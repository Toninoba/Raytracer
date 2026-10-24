# JSON World Definition Documentation

This document explains how to define a 3D scene (a "World") using JSON for the `WorldBuilder` parser.

## Root Structure

The root of the JSON file must be an object containing a single `world` property.

```json
{
  "world": {
    "camera": { ... },
    "lights": [ ... ],
    "objects": [ ... ]
  }
}
```

*   **`camera`** *(Required)*: An object defining the camera parameters.
*   **`lights`** *(Optional)*: An array of light objects illuminating the scene.
*   **`objects`** *(Optional)*: An array of shape objects defining the geometry of the scene.

---

## Camera

The camera configuration defines how the scene is viewed. It requires horizontal/vertical sizes, field of view, and a view transformation.

```json
"camera": {
  "hsize": 800,
  "vsize": 600,
  "fov": 90,
  "viewTransform": {
    "from": [0, 1.5, -5],
    "to": [0, 1, 0],
    "up": [0, 1, 0]
  }
}
```

### Properties
*   **`hsize`** *(Number, Required)*: Horizontal resolution of the canvas/image.
*   **`vsize`** *(Number, Required)*: Vertical resolution of the canvas/image.
*   **`fov`** *(Number, Required)*: Field of view in degrees.
*   **`viewTransform`** *(Object, Required)*: Defines the position and orientation of the camera.
    *   **`from`** *(Array of 3 Numbers, Required)*: The [x, y, z] position of the camera.
    *   **`to`** *(Array of 3 Numbers, Required)*: The [x, y, z] point the camera is looking at.
    *   **`up`** *(Array of 3 Numbers, Required)*: The [x, y, z] vector defining which way is "up".

---

## Lights

Currently, the engine supports Point Lights. These are defined within the `lights` array.

```json
"lights": [
  {
    "type": "PointLight",
    "position": [-10, 10, -10],
    "intensity": [1, 1, 1]
  }
]
```

### Properties
*   **`type`** *(String, Required)*: Must be `"PointLight"`.
*   **`position`** *(Array of 3 Numbers, Required)*: The [x, y, z] coordinates of the light source.
*   **`intensity`** *(Array of 3 Numbers, Required)*: The RGB color/intensity of the light source (e.g., `[1, 1, 1]` for white).

---

## Objects (Shapes)

The `objects` array contains all the geometric shapes in your world.

```json
"objects": [
  {
    "type": "sphere",
    "transform": [ ... ],
    "material": { ... },
    "pattern": { ... }
  }
]
```

### Properties
*   **`type`** *(String, Required)*: The type of shape. Case-insensitive. Supported types:
    *   `"sphere"`
    *   `"plane"`
    *   `"cube"`
    *   `"cylinder"`
    *   `"cone"`
*   **`transform`** *(Array of Objects, Optional)*: Geometric transformations (see [Transformations](#transformations)).
*   **`material`** *(Object, Optional)*: Surface properties (see [Materials](#materials)).
*   **`pattern`** *(Object, Optional)*: Surface patterns (see [Patterns](#patterns)).

### Specific Shape Properties
If the `type` is `"cylinder"` or `"cone"`, the following optional properties can also be provided:

*   **`min`** *(Number, Optional)*: The minimum extent/truncation of the shape along the y-axis.
*   **`max`** *(Number, Optional)*: The maximum extent/truncation of the shape along the y-axis.
*   **`closed`** *(Boolean, Optional)*: If `true`, the ends of the cylinder/cone are capped.

---

## Transformations

Transformations alter the size, rotation, and position of objects or patterns. They are applied in the order they appear in the array.

```json
"transform": [
  { "scaling": [2, 2, 2] },
  { "rotateX": 45 },
  { "translate": [1, 2, -1] }
]
```

### Supported Operations:
*   **`translate`**: `[x, y, z]` (Array of 3 numbers)
*   **`scaling`**: `[x, y, z]` (Array of 3 numbers)
*   **`rotateX`**: `degrees` (Number)
*   **`rotateY`**: `degrees` (Number)
*   **`rotateZ`**: `degrees` (Number)
*   **`shearing`**: `[xy, xz, yx, yz, zx, zy]` (Array of 6 numbers)

---

## Materials

Materials dictate how a shape interacts with light.

```json
"material": {
  "color": [1, 0.2, 1],
  "ambient": 0.1,
  "diffuse": 0.9,
  "specular": 0.9,
  "shininess": 200,
  "reflective": 0.5,
  "transparency": 0.9,
  "refractiveIndex": 1.5
}
```

### Properties
All properties are **optional** (defaults depend on the internal engine implementation).
*   **`color`** *(Array of 3 Numbers, optional)*: RGB base color of the material.
*   **`ambient`** *(Number, optional)*: Ambient reflection constant.
*   **`diffuse`** *(Number, optional)*: Diffuse reflection constant.
*   **`specular`** *(Number, optional)*: Specular reflection constant.
*   **`shininess`** *(Number, optional)*: Specular highlight size/shininess.
*   **`reflective`** *(Number, optional)*: Reflectivity (0.0 to 1.0).
*   **`transparency`** *(Number, optional)*: Transparency (0.0 to 1.0).
*   **`refractiveIndex`** *(Number, optional)*: Index of refraction (e.g., 1.0 for vacuum, 1.5 for glass).

---

## Patterns

Patterns can be applied over materials to create procedural textures.

```json
"pattern": {
  "type": "CheckerPattern",
  "colorA": [1, 1, 1],
  "colorB": [0, 0, 0],
  "transform": [
    { "scaling": [0.5, 0.5, 0.5] }
  ]
}
```

### Properties
*   **`type`** *(String, Required)*: The type of pattern. Supported types:
    *   `"CheckerPattern"`
    *   `"GradientPattern"`
    *   `"RingPattern"`
    *   `"StripedPattern"`
*   **`colorA`** *(Array of 3 Numbers, Required)*: First RGB color of the pattern.
*   **`colorB`** *(Array of 3 Numbers, Required)*: Second RGB color of the pattern.
*   **`transform`** *(Array of Objects, Optional)*: Transformations applied exclusively to the pattern space (same syntax as shape transformations).