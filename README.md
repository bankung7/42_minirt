# 42_minirt

## Mandotory
- must use `miniLIbX`.
- Window management like switching, minimization and etc.
- Content of the window must remain unchanged and be adjusted for window resolution change.
- At least 3 simple geometrai object: plane, sphere and cylinder.
- Handle intersection and inside the object.
- Must be able to resize the object: diameter for sphere, width and height of cylinder.
- Translation and rotation: light and camera except sphere and light cannot rotate.
- Light Management: 
  spot brightness, hard shadow, ambient lighting and diffuse lighting. 
  The objects are never completely dark.
 - Program Display:
  Pressing ESC and clicking the red cross to close the window and cleanly exit.
  Use `images` of miniLibX.
  
 ## Bonus
 - Specular reflection to have full `Phong reflection` model.
 - Color disruption: `checker board`.
 - Colored and multi-spot lights.
 - One other 2ndf degree object: Cone, Hyperboloid, Paraboloid or etc.
 - Handle bump map textures.

## Parsing
- file in .rt
- Each type of element can be separated by one or more line break(s).
- Each type of information from an element can be separated by one or more space(s).
- Each type of element can be set in any order in the file.
- Elements which are defined by a capital letter can only be declared once in the scene.
- Ambient lightning, Camera, Light, Sphere, Plane and Cylinder

```
// Example of .rt file //
A 0.2 255,255,255
C -50,0,20 0,0,0 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

- Any misconfiguration must `exit` and return `Error\n` followed by explicit error message.  

## Vector structure and its operations
