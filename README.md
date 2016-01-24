# BlockingVR
A UE4 engine plugin that provide a blueprint interface to enable level editing while using VR Preview.<br>
The plugin is HMD agnostic supporting any HMD that uses VR preview.<br>
The plugin support basic level editing functionality which includes:<br>
* Addition and deletion of basic actor types.
* Adjusting the transform of actors.
* Copy and pasting actors.
* Setting the material of StaticMeshActors.
* Setting the basic properties of lights.

The plugin also comes with an example interface that utilizes an Xbox controller<br>
called BVRExamplePawn.

## Installation & setup

If you are not compiling UE4's engine from source you should download one of the latest precompilied windows binaries:<br>
* [engine version 4.9.2](http://www.mediafire.com/download/73yup04cv7a11zj/BlockingVR4.9Beta2-Binary.rar)<br>
* [engine version 4.10.2](http://www.mediafire.com/download/is2hqqt3517shvj/BlockingVR4.10Beta2-Binary.rar)

The contents of the plugin should be copied to your UE4 installation location.<br>
so that the BlockingVR folder resides in the engines plugin folder.<br>
i.e C:\UE4\Engine\Plugins\BlockingVR<br>
Once copied over the plugin will need enabling and the engine restarting<br>
by opening the plugin's window in UE4 and location the plugin under the "VR" subcategory.

## Using BlockingVR
#### Important! ####
**BlockingVR currently does'nt support level streaming or world composition.<br>**
**To use BlockingVR under these circumstances the sub-level umap file you wish to work on<br>**
**should be opened directly in the editor.**
### The BlockingVR Collection
![](http://i.imgur.com/WbWD2R0.jpg)<br>
With the plugin enabled every project with have a collection created called "BlockingVRCollection". This collection will be created at each editor startup if the collection does not already exist. Any actor, staticmesh, particle or material
assets added to this collection will show up in the blockingVRExamplePawn menu's for later use when editing. To understand how collections work please see the [UE4 documentation](https://docs.unrealengine.com/latest/INT/Engine/Content/Browser/UserGuide/Collections/index.html) on collections.

### Enable BVRExamplePawn
![](http://i.imgur.com/UlptBnF.jpg)<br>
The BVRExamplePawn is an example interface that uses a standard Xbox controller for user input.<br>
To enable the BVRExamplePawn simply switch your gamemode under world settings to "BVRExampleGameMode".<br>
And then start VR preview. To disable simply switch your gamemode back.

### BVRExamplePawn controls
#### Standard movement
* With no menu's current showing standard movement is controlled using the XBox controllers left and right sticks.

#### Traversing menu's
* The controllers **left and right D-Pad** are used for changing the context sesitive menu's.
* The controllers **up and down D-Pad** are used for changing the menu's selection.

#### Changing Values
* Left and right on the controllers **Left Stick** will change the current selections value.
* When using the color picker the **Left Stick** will move the cursor within the color wheel.
* When using the color picker the **Right Stick** up and down will alter the V value of HSV.

#### Setting snap size
* With No menu's showing(or with the location context menu visible) the **X button** will cycle through location snap values for the movement of actors.
* With the scale context menu showing this will cycle through scale snap values.
* With the rotation context menu this will cycle though rotation snap values.

#### Delete actor
* With no menu's showing the **Y button** will delete the currently highlighted actor.

#### Copy paste actor
* With no menu's showing the **Left Bumper** will copy the currently highlighted actor.
* With no menu's showing the **Right Bumper** will Paste the copied actor at the cursors current location.

#### Select Actor
* With no menu's showing the **A button** will attempt to select the currently highlighted actor and bring up any relevent context menu's.

#### Deselect Actor/Exit menu's
* The **B button** will Deselect the currently selected actor and/or exit current context menu's.

#### Spawn Actor
* the **A button** will attempt to spawn an actor of current type selected from context menu at the current cursor location.

#### Hide/Show all handles
* The **Start button** will toggle the visibility of all actor icons.

#### Hide/Show all debug meshes
* The **Back button** will toggle the visibility of all light debug meshes.

#### Hide/Show dynamic lighting
* **Right Stick Click** will toggle dynamic lighting on and off.

#### Pickup/Drop Actor
* The **Right Trigger** will attempt to pickup/drop the currently highlighted actor.

### ContextMenu's
####Location Menu
![](http://imgur.com/Lb0fVWG.jpg)<br>
* Available when selecting any selectable actor.

####Rotation Menu
![](http://imgur.com/l7Alaut.jpg)<br>
* Available when selecting any selectable actor.

####Scale Menu
![](http://imgur.com/vr9HrXk.jpg)<br>
* Available when selecting any selectable non-light actor.

####Color and Intensity Menu
![](http://imgur.com/4VAxEj6.jpg)<br>
* Available when any light is selected.

####Point Light Menu
![](http://imgur.com/UoevTjz.jpg)<br>
* Available when a point light is selected.

####Spot Light Menu
![](http://imgur.com/rHkJ4Vc.jpg)<br>
* Available when a spot light is selected.

####Directional Light Menu
![](http://imgur.com/AqY8AJj.jpg)<br>
* Available when a directional light is selected.

####Primatives Menu
![](http://imgur.com/SOdVRAV.jpg)<br>
* Available when no actor is selected.
* Spawn the highlighted primative at current cursor location with **A Button**

####Lights Menu
![](http://imgur.com/v5mFY1A.jpg)<br>
* Available when no actor is selected.
* Spawn the highlighted light at current cursor location with **A Button**
* All new lights default to stationary mobility.

####Actors Menu
![](http://imgur.com/hgLZEon.jpg)<br>
* Available when no actor is selected.
* Only visible if at least one actor has been added to the "BlockingVRCollection" collection.
* Spawn the highlighted actor at current cursor location with **A Button**
* **if the actor has no collision you will not be able to delete/manipulate after.**

####Static Meshes Menu
![](http://imgur.com/Fsoqy0o.jpg)<br>
* Available when no actor is selected.
* Only visible if at least one static mesh has been added to the "BlockingVRCollection" collection.
* Spawn the highlighted static mesh at current cursor location with **A Button**
* **if the mesh has no collision you will not be able to delete/manipulate after.**

####Particles Menu
![](http://imgur.com/JxJI3cj.jpg)<br>
* Available when no actor is selected.
* Only visible if at least one particle system has been added to the "BlockingVRCollection" collection.
* Spawn the highlighted particle system at current cursor location with **A Button**

####Materials Menu
![](http://imgur.com/yR6x2Ho.jpg)<br>
* Available when no actor is selected.
* Only visible if at least one material has been added to the "BlockingVRCollection" collection.
* Attempt to apply the highlighted material to the currently highlighted StaticMeshActor with **A Button**

## Creating your own interface
TBC...
