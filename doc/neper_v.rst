.. |translate| replace:: :data:`translate(<dist_x>,<dist_y>,<dist_z>)`: translate by distances :data:`<dist_x>`, :data:`<dist_y>` and :data:`<dist_z>` along :data:`x`, :data:`y` and :data:`z`, respectively
.. |rotate| replace:: :data:`rotate(<axis_x>,<axis_y>,<axis_z>,<angle>)`: rotate about the center and by an axis/angle pair (angle expressed in degrees)
.. |scale| replace:: :data:`scale(<fact_x>,<fact_y>,<fact_z>)`: scale by :data:`<fact_x>`, :data:`<fact_y>` and :data:`<fact_z>` along :data:`x`, :data:`y` and :data:`z`, respectively
.. |data_description| replace:: This can be done either directly, by providing one or several values (e.g. the RGB channel values for color) or indirectly, e.g. using scalar values that are converted in color using a given *color scheme*.  In this case (and for real-type data), a scale image is also generated, and its properties (minimum, maximum and tick values) can be set.

.. index::
   single: -V

.. _neper_v:

Visualization Module (-V)
=========================

Module -V is the module for visualizing tessellations, meshes and simulation results as publication-quality PNG images or VTK files, for interactive visualization. Results can be defined from internal data, data loaded from external files or a simulation directory as generated by module -S.  For the PNG images, it is possible to set different attributes of the tessellations and meshes such as the node coordinates, or the colors and transparencies of the different entities. Point data can also be represented, using symbols of specified sizes and colors. Slice views can also be generated.

Contrary to other modules, module -V processes the command arguments one after the other. Typically, module -V can be used to visualize tessellations, meshes, points, or results of a simulation directory (on the mesh).  The aspects of all entities (tessellation polyhedra, faces, edges and vertices, 3D, 2D, 1D and 0D mesh elements and nodes, and points) can be set in detail (options :data:`-data*`). In the case of a PNG output file, the scene itself can also be set in detail: visibility of the different entities (options :data:`-show*`), camera position and angle, projection type, image size, etc. (options :data:`-camera*` or :data:`-image*`).  The coordinate system can also be added.

Here is what a typical run of module -V looks like:

.. code-block:: console

  $ neper -V n10-id1.tess,n10-id1.msh -dataelsetcol id -print img

  ========================    N   e   p   e   r    =======================
  Info   : A software package for polycrystal generation and meshing.
  Info   : Version 4.0.0
  Info   : Built with: gsl|muparser|opengjk|openmp|nlopt|libscotch (full)
  Info   : Running on 8 threads.
  Info   : <https://neper.info>
  Info   : Copyright (C) 2003-2021, and GNU GPL'd, by Romain Quey.
  Info   : No initialization file found (`/home/rquey/.neperrc').
  Info   : ---------------------------------------------------------------
  Info   : MODULE  -V loaded with arguments:
  Info   : [ini file] (none)
  Info   : [com line] n10-id1.tess,n10-id1.msh -dataelsetcol id -print img
  Info   : ---------------------------------------------------------------
  Info   : Loading tessellation...
  Info   :     [i] Parsing file `n10-id1.tess'...
  Info   :     [i] Parsed file `n10-id1.tess'.
  Info   : Loading mesh...
  Info   :     [i] Parsing file `n10-id1.msh'...
  Info   :     [i] Parsed file `n10-id1.msh'.
  Info   : Reconstructing mesh...
  Info   : Reading data (elset3d, col)...
  Info   : Printing image...
  Info   :     [o] Writing file `img.pov'...
  Info   :   - Printing mesh...
  Info   :     > Reducing data...
  Info   :       . 3D...
  Info   :       . 2D...
  Info   :       . Number of 3D elt faces reduced by  90% (to 418).
  Info   :       . Number of 3D elt edges reduced by  50% (to 627).
  Info   :       . Number of 0D elts      reduced by 100% (to 0).
  Info   :     [o] Wrote file `img.pov'.
  Info   :   - Generating png file (1200x900 pixels)...
  Info   :     [o] Writing file `img.png'...
  Info   :     [o] Wrote file `img.png'.
  Info   : Printing scale...
  Info   : Elapsed time: 1.546 secs.
  ========================================================================

Arguments
---------

Prerequisites
~~~~~~~~~~~~~

.. option:: -povray <binary>

  Specify the POV-Ray command or the path to the POV-Ray binary (for generating PNG images).

  **Default value**: :data:`povray`.

Input Data
~~~~~~~~~~

.. option:: <file_name1>,<file_name2>,...

  Specify the names of the input file(s) or directory. The file(s) can be a :ref:`tess_file`, a :ref:`tesr_file`, a :ref:`mesh_file`, or a :ref:`position_file` (for points), and the directory can be a :ref:`simulation_directory`.

  **Default value**: -.

When a simulation directory is loaded as input, it is possible to specify the simulation step to consider.

.. option:: -simstep <step>

  Specify the simulation step (:data:`0` for the initial state).,

  **Default value**: :data:`0`.

The data internal to the simulation directory have the same status as internal data (such as, for instance, the nominal element orientations stored in the mesh file) and can therefore be loaded (with options :data:`-data*`) more simply than with standard external files.  For example, coloring elements from orientations can be done using :data:`-simstep 2 -dataeltcol ori`, instead of the standard :data:`-dataeltcol "ori:file(<simulation_directory>/res/ori/ori.step2)"`.

Space Options
~~~~~~~~~~~~~

The following option enables the definition of the space which the input data (tessellation, mesh, point, etc.) are defined in.  The space is most generally real (physical) space, but can be defined as Rodrigues orientation space, which makes it possible to account for its distortion [#space]_.

.. option::  -space <space> (secondary option)

  Specify the space which the input data are defined in, which can be:

  - :data:`real` for real space;
  - :data:`rodrigues` for Rodrigues orientation space.

  **Default value**: :data:`real`.

Tessellation Data Loading and Rendering
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following options enable the definition of the properties (color and size) of the tessellation cells or entities (polyhedra, faces, edges and vertices). |data_description|

.. index::
   single: -datacellcol
   single: -datapolycol
   single: -datafacecol
   single: -dataedgecol
   single: -datavercol
   single: -dataseedcol
   single: -datavoxcol
   single: -datavoidvoxcol
   single: -datavoxedgecol
   single: -data...col

.. option:: -data{cell,poly,face,edge,ver,seed,vox,voidvox,voxedge}col <color>

  Specify the colors, which can be done in two main different ways.

  **Colors can be specified directly**:

  - a color (see :ref:`colors_and_color_maps`);
  - :data:`file(<file_name>)`: individual colors to load from a :ref:`data_file` (see :ref:`colors_and_color_maps`).

  **Colors can be set from data using an argument of the general form** :data:`<data_type>:\<data_value\>`, which can be shortened to :data:`<data_value>` in the frequent case where the data type can be unambiguously determined from the data value.  The possibilities are:

  - :data:`int:\<data_value\>`: integer values represented using a color palette,  which can be:

    - an integer value;
    - an expression based on the variables defined in :ref:`tessellation_keys`, such as :data:`id` or :data:`mode`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`real:\<data_value\>`: real values represented using a smooth color scale, which can be:

    - a real value;
    - an expression based on the variables described in :ref:`tessellation_keys`, such as :data:`x` or :data:`vol`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`ori:\<data_value\>`: crystal orientations (when applicable), which can be:

    - :data:`orientation`: an orientation (see :ref:`rotations_and_orientations`);
    - :data:`internal`: internal orientations;
    - :data:`file(<file_name>,[des=<descriptor>])`: individual values to load from a :ref:`data_file` (see :ref:`rotations_and_orientations`).

  - :data:`disori:\<data_value\>` (only for :data:`vox`): crystal disorientations (the rotation with respect to the nominal cell orientation, when applicable), which can be:

    - :data:`<disorientation>`: a disorientation (see :ref:`rotations_and_orientations`);
    - :data:`internal`: internal disorientations;
    - :data:`file(<file_name>,[des=<descriptor>])`: individual values to load from a :ref:`data_file` (see :ref:`rotations_and_orientations`).

  See also option :data:`-data...colscheme`.

  **Default value**: :data:`id` for cells, :data:`white` for faces, :data:`black` for edges and vertices, :data:`gray` for seeds, voxels and void voxels, :data:`black` for voxel edges.

.. index::
   single: -datacellcolscheme
   single: -datapolycolscheme
   single: -datafacecolscheme
   single: -dataedgecolscheme
   single: -datavercolscheme
   single: -dataseedcolscheme
   single: -datavoxcolscheme
   single: -datavoidvoxcolscheme
   single: -datavoxedgecolscheme
   single: -data...colscheme

.. option:: -data{cell,poly,face,edge,ver,seed,vox}colscheme <col_scheme>

  Specify the color scheme used to get colors from the data loaded with option :data:`-data...col`.
  The type of color scheme depends on the type of data.

  - For integer values, the color scheme is :data:`palette` (see :ref:`colors_and_color_maps`);

  - For real values, the available color schemes are described in :ref:`colors_and_color_maps`;

  - For crystal orientations (cubic symmetry is assumed), the color scheme can be:

    - :data:`ipf[(<dir>)]`: IPF coloring using direction :data:`<dir>`, which can be :data:`x`, :data:`y` or :data:`z` (default :data:`z`);

    - :data:`rodrigues[(<max>)]`: Rodrigues vector coloring, where :data:`<max>` is the half-length along a direction (default is the fundamental region);

    - :data:`axis`: rotation axis coloring;
    - :data:`angle[(<max>)]`: rotation angle coloring, where :data:`<max>` is the maximum angle (in radian (default is the fundamental region);
    - :data:`axis-angle[(<max>[,absolute])]` for rotation axis / angle coloring, where :data:`<max>` is the maximum angle (in radian) and :data:`absolute` makes it so that the absolute values of the axis components are used.

  **Default value**: :data:`palette` for integer values, :data:`viridis` for real values, and :data:`rodrigues` for crystal orientations.

.. index::
   single: -datacelltrs
   single: -datapolytrs
   single: -datafacetrs
   single: -dataedgetrs
   single: -datavertrs
   single: -dataseedtrs
   single: -data...trs

.. option:: -data{cell,poly,face,edge,ver,seed}trs <transparency>

  Specify the transparency (a value from 0 to 1), which can be:

  - a real value;
  - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  **Default value**: :data:`0`.

.. option:: -data{cell,poly,face,edge,ver,seed,vox}scale <scale>

  Specify the scale relative to the :data:`-data...col real` data, which can be:

  - :data:`<min>:\<max\>`: minimal and maximal values;
  - :data:`<min>:\<inter1\>:...:\<max\>`: minimal, intermediate and maximal values.

  When only minimal and maximal values are specified, the scale ticks are set automatically.  When intermediate values are specified, the scale ticks are the specified values.

  The scale ticks have the same format as the minimal value.

  **Default value**: :data:`<data_minimum>:\<data_maximum\>`.

.. option:: -data{cell,poly,face,edge,ver,seed,vox}scaletitle <title>

  Specify the title of the scale relative to the :data:`-data...col real` data.

  **Default value**: -.

.. option:: -data{edge,ver,seed,voxedge}rad <rad>

  Specify the radii, which can be:

  - a real value;
  - :data:`file(<file_name>)`: individual values to load values from a :ref:`data_file`.

  **Default value**: tessellation dependent.

Mesh Data Loading and Rendering
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following options enable the definition of the properties (color, size, etc.) of the mesh entities (3D, 2D, 1D and 0D elements and elsets, nodes, and full mesh).  :data:`elt` and :data:`elset` refer to the elements and elsets of higher dimensions.  The dimension can be also be specified explicitly, as in :data:`elt2d` or :data:`elset2d`.  :data:`node` represents all nodes, and :data:`mesh` the full mesh.  |data_description|

.. option:: -data{elt,elset,node,elt{0-3}d,elset{0-3}d,elt{2,3}dedge,mesh}col <color>

  Specify the colors, which can be done in two main different ways.

  **Colors can be specified directly**:

  - :data:`<value>`: a color (see :ref:`colors_and_color_maps`);
  - :data:`file(<file_name>)`: individual colors to load from a :ref:`data_file` (see :ref:`colors_and_color_maps`);
  - :data:`from_nodes`: colors interpolated from the node colors (defined with :data:`-datanodecol`).

  **Colors can be set from data using an argument of the general form** :data:`<data_type>:\<data_value\>`, which can be shortened to :data:`<data_value>` in the frequent case where the data type can be unambiguously determined from the data value.  The possibilities are:

  - :data:`int:\<data_value\>`: integer values represented using a color palette,  which can be:

    - an integer value;
    - an expression based on the variables defined in :ref:`tessellation_keys`, such as :data:`id` or :data:`mode`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`real:\<data_value\>`: real values represented using a smooth color scale, which can be:

    - a real value;
    - an expression based on the variables described in :ref:`tessellation_keys`, such as :data:`x` or :data:`vol`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`vector:\<data_value\>`: vectorial values (only for VTK output), which can be:

    - a simulation result (see :ref:`simulation_results`);
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`tensor:\<data_value\>`: tensorial values (only for VTK output), which can be:

    - a simulation result (see :ref:`simulation_results`);
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.  The file can contain either 9 components or only 6 components, in which case Voigt notation is assumed.

  - :data:`ori:\<data_value\>`: crystal orientations (when applicable), which can be:

    - an orientation (see :ref:`rotations_and_orientations`);
    - :data:`internal`: internal orientations;
    - :data:`file(<file_name>,[des=<descriptor>])`: individual orientations to load from a :ref:`data_file` (see :ref:`rotations_and_orientations`).

  The color schemes used to determine the colors from the data can be fine-tuned using options :data:`-dataeltcolscheme` or :data:`-dataelsetcolscheme`.

  **Default value**: :data:`-dataelsetcol id` (elsets of higher dimension colored, other elsets white, element edges black)


.. option:: -data{elt,elset,node,elt{0-3}d,elset{0-3}d}colscheme <col_scheme>

  Specify the color scheme used to get colors from the data loaded with option :data:`-data...col`.
  The type of color scheme depends on the type of data.

  - For integer values, the color scheme is :data:`palette` (see :ref:`colors_and_color_maps`);

  - For real values, the available color schemes are described in :ref:`colors_and_color_maps`;

  - For crystal orientations (cubic symmetry is assumed), the color scheme can be:

    - :data:`ipf[(<dir>)]`: IPF coloring using direction :data:`<dir>`, where :data:`dir` is one of :data:`x`, :data:`y` or :data:`z` (default :data:`z`);

    - :data:`rodrigues[(<max>)]`: Rodrigues vector coloring, where :data:`<max>` is the half-length along a direction (default is the fundamental region);

    - :data:`axis`: rotation axis coloring;
    - :data:`angle[(<max>)]`: rotation angle coloring, where :data:`<max>` is the maximum angle (in radian (default is the fundamental region);
    - :data:`axis-angle[(<max>[,absolute])]` for rotation axis / angle coloring, where :data:`<max>` is the maximum angle (in radian) and :data:`absolute` makes it so that the absolute values of the axis components are used.

  **Default value**: :data:`palette` for integer values, :data:`viridis` for real values, and :data:`rodrigues` for crystal orientations.

.. option:: -data{elt,elset,node,elt{0-3}d,elset{0-3}d}scale <scale>

  Specify the scale relative to the :data:`-data...col real` data, which can be:

  - :data:`<min>:\<max\>`: minimal and maximal values;
  - :data:`<min>:\<inter1\>:...:\<max\>`: minimal, intermediate and maximal values.

  When only minimal and maximal values are specified, the scale ticks are set automatically.  When intermediate values are specified, the scale ticks are the specified values.

  The scale ticks have the same format as the minimal value.

  **Default value**: :data:`<data_minimum>:\<data_maximum\>`.

.. option:: -data{elt,elset,node,elt{0-3}d,elset{0-3}d}scaletitle <title>

  Specify the title of the scale relative to the :data:`-data...col real` data.

  **Default value**: -.

.. option:: -data{elt{0,1}d,node,elt{2,3}dedge,elset{0,1}d}rad <rad>

  Specify the radii, which can be:

  - a real value;
  - :data:`file(<file_name>)`: individual values to load values from a :ref:`data_file` (not for :data:`*edge*`).

  **Default value**: mesh dependent.


The following options enable the loading of node positions.

.. option:: -datanodecoo <coo>

  Specify the coordinates of the nodes, which can be done in two main different ways.

  **Coordinates can be specified directly as follows:**

  - :data:`file(<file_name>)`: individual coordinates to load from a :ref:`position_file`.

  **Coordinates can be set from data using an argument of the general form** :data:`<data_type>:\<data_value\>`:

  - :data:`disp:file(<file_name>)`: individual displacements to load from a :ref:`data_file` (formatted as a :ref:`position_file`);

  - :data:`coo`: load coordinates from the simulation directory and step specified in input.

  **Default value**: -.

.. option:: -datanodecoofact <fact>

  Specify the value of the scaling factor to apply to the displacements of the nodes.

  **Default value**: :data:`1`.

Point Data Loading and Rendering
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following options enable the definition of the properties (color, shape, size, etc.) of points loaded as input. |data_description|

.. option:: -datapointcol <color>

  Specify the colors of the points, which can be done in two main different ways.

  **Colors can be specified directly**:

  - a color (see :ref:`colors_and_color_maps`);
  - :data:`file(<file_name>)`: individual colors to load from a :ref:`data_file` (see :ref:`colors_and_color_maps`).

  **Colors can be set from data using an argument of the general form** :data:`<data_type>:\<data_value\>`, which can be shortened to :data:`<data_value>` in the frequent case where the data type can be unambiguously determined from the data value.  The possibilities are:

  - :data:`int:\<data_value\>`: integer values represented using a color palette,  which can be:

    - an integer value;
    - an expression based on the variables defined in :ref:`tessellation_keys`, such as :data:`id` or :data:`mode`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  - :data:`real:\<data_value\>`: real values represented using a smooth color scale, which can be:

    - a real value;
    - an expression based on the variables described in :ref:`tessellation_keys`, such as :data:`x` or :data:`vol`, which allows to define individual values;
    - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  See also option :option:`-datapointcolscheme`.

  **Default value**: :data:`gray`.


.. option:: -datapointcolscheme <col_scheme>

  Specify the color scheme used to get colors from the data loaded with option :option:`-datapointcol`.
  The type of color scheme depends on the type of data.

  - For integer values, the color scheme is :data:`palette` (see :ref:`colors_and_color_maps`);

  - For real values, the available color schemes are described in :ref:`colors_and_color_maps`;

  **Default value**: :data:`palette` for integer values and :data:`viridis` for real values.

.. option:: -datapointtrs <transparency>

  Specify the transparency of the points (a value from 0 to 1), which can be:

  - a real value;
  - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`.

  **Default value**: :data:`0`.

.. option:: -datapointscale <scale>

  Specify the scale relative to the :data:`-datapointcol real` data, which can be:

  - :data:`<min>:\<max\>`: minimal and maximal values;
  - :data:`<min>:\<inter1\>:...:\<max\>`: minimal, intermediate and maximal values.

  When only minimal and maximal values are specified, the scale ticks are set automatically.  When intermediate values are specified, the scale ticks are the specified values.

  The scale ticks have the same format as the minimal value.

  **Default value**: :data:`<data_minimum>:\<data_maximum\>`.

.. option:: -datapointscaletitle <title>

  Specify the title of the scale relative to the :data:`-datapointcol real` data.

  **Default value**: -.

.. option:: -datapointcoo <coo>

  Specify the coordinates of the points, which can be done in two main different ways.

  **Coordinates can be specified directly as follows:**

  - :data:`file(<file_name>)`: individual coordinates to load from a :ref:`position_file`.

  **Coordinates can be set from data using an argument of the general form** :data:`<data_type>:\<data_value\>`:

  - :data:`disp:file(<file_name>)`: individual displacements to load from a :ref:`data_file` (formatted as a :ref:`position_file`);

  - :data:`coo`: load coordinates from the simulation directory and step specified in input.

  **Default value**: -.

.. option:: -datapointcoofact <fact>

  Specify the value of the scaling factor to apply to the displacements of the points.

  **Default value**: :data:`1`.

.. option:: -datapointrad <rad>

  Specify the radii (and shapes) of the points, which can be:

  - a real value;
  - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file` (not for :data:`*edge*`).
  - :data:`cube:file(<file_name>)`: cubes of properties to load from a :ref:`data_file`.  The file must contain, for each point, the radius (half of the edge length) and the coordinates of the three axes (which also is the rotation matrix that brings the reference axes into coincidence with the cube axes).
  - :data:`cylinder:file(<file_name>)`: cylinders of properties to load from a :ref:`data_file`.  The file must contain, for each point, the radius, the length and the coordinates of the axis.
  - :data:`arr:file(<file_name>)`: arrows of properties to load from a :ref:`data_file`.  The file must contain, for each point, the radius, the length and the coordinates of the axis.
  - :data:`disc:file(<file_name>)`: discs of properties to load from a :ref:`data_file`. The file must contain, for each point, the radius and the coordinates of the axis.
  - :data:`ell:file(<file_name>)`: ellispoids of properties to load from a :ref:`data_file`.  The file must contain, for each point, the three radii and the coordinates of the three axes.
  - :data:`tor:file(<file_name>)`: torus of properties to load from a :ref:`data_file`.  The file must contain, for each point, the major radius (center to center line), the minor radius and the coordinates of the normal axis.

  **Default value**: point set dependent.

.. option:: -datapointedgerad <rad>

  Specify the radius of the point edges (represented as symbols), which can be any real value (:math:`\geq0`).

  **Default value**: :data:`0`.

.. option:: -datapointedgecol <color>

  Specify the color of the point edges (represented as symbols), which can be a color as described in :ref:`colors_and_color_maps`.


  **Default value**: :data:`black`.

Coordinate System Rendering
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. option:: -datacsyscoo <coo_x>:<coo_y>:<coo_z>

  Specify the coordinates of the origin of the coordinate system.

  **Default value**: :data:`0:0:0`.

.. option:: -datacsyslength <length>

  Specify the length of the coordinate system axes.

  **Default value**: :data:`0.2`.

.. option:: -datacsysrad <rad>

  Specify the radius of the coordinate system axes.

  **Default value**: :data:`0.01`.

.. option:: -datacsyslabel <label_x>:<label_y>:<label_z>

  Specify the labels of the coordinate system axes.

  **Default value**: :data:`X1:X2:X3`.

.. option:: -datacsyscol <color>

  Specify the color of the coordinate system, which can be a color as described in :ref:`colors_and_color_maps`.

  **Default value**: :data:`32:32:32`.

.. option:: -datacsysfontsize <size>

  Set the font size of the labels of the coordinate system axes.

  **Default value**: :data:`1`.

Slice Settings
~~~~~~~~~~~~~~

.. option:: -slicemesh <plane1>,<plane2>,...

  Plot one (or several) slice(s) of the mesh.  A slicing plane is defined by its equation, such as :data:`x=0` or :data:`0.12*x+0.34*y+0.56*z=0.78`.

  **Default value**: -.

Show Settings
~~~~~~~~~~~~~

The following options apply to the full tessellations, mesh or points.

.. option:: -show{tess,tesr,mesh,meshslice,point,csys} <logical>

  Show or hide a full tessellation, mesh, etc.

  **Default value**: :data:`1` for the more informative data (mesh slice :math:`>` mesh :math:`>` tessellation) and :data:`0` for others.

The following option applies to a tessellation or a raster tessellation.

.. option:: -show{cell,poly,face,edge,ver,seed,faceinter,vox,voidvox} <logical>

  Specify the entities to show. The argument can be:

  - :data:`1` or :data:`all`: all;
  - any expression based on the keys listed in :ref:`tessellation_keys` or :ref:`raster_tessellation_keys`;
  - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`;
  - :data:`0` or :data:`none`: none.

  For faces, etc., :data:`cell_shown` and :data:`poly_shown` can also be used.

  **Default value**: :data:`all` for cells and edges, :data:`none` for others.

The following options apply to the entities of the mesh.  The options apply to 3D elements (:data:`elt3d`) and element sets (:data:`elset3d`), 2D elements (:data:`elt2d`) and element sets (:data:`elset2d`), 1D elements (:data:`elt1d`) and element sets (:data:`elset1d`), 0D elements (:data:`elt0d`) and element sets (:data:`elset0d`), and nodes (:data:`nodes`). Also note that the :data:`elt` and :data:`elset` can be used to denote the highest-dimension elements and elsets.

.. option:: -show{elt,elset,elt{0-3}d,elset{0-3}d,node} <logical>

  Specify the entities to show. The argument can be:

  - :data:`1` or :data:`all` for all;
  - any expression based on the keys listed in :ref:`mesh_keys`;
  - :data:`file(<file_name>)`: individual values to load from a :ref:`data_file`;
  - :data:`0` or :data:`none`: none.

  **Default value**: :data:`1` if highest mesh dimension is 3 and :data:`0` otherwise.

Camera Settings
~~~~~~~~~~~~~~~

.. option:: -cameracoo <coo_x>:<coo_y>:<coo_z>

  Specify the coordinates of the camera. The coordinates can be defined as expressions based on the following variables:

  - :data:`x`, :data:`y` and :data:`z`: the center of the tessellation or mesh (if both a tessellation and a mesh have been loaded, the mesh is considered);
  - :data:`length`: the average length of the domain (:data:`1` for a unit cube);
  - :data:`vx`, :data:`vy` and :data:`vz`: the coordinates of the shift vector, which are equal to :data:`3.462`, :data:`-5.770` and :data:`4.327`, respectively in 3D, and :data:`0`, :data:`0` and :data:`8`, respectively, in 2D.

  **Default value**: :data:`x+length*vx:y+length*vy:z+length*vz`.

.. option:: -cameralookat <coo_x>:<coo_y>:<coo_z>

  Specify the coordinates of the camera look-at point.  The coordinates can be defined as expressions based on the following variables:

  - :data:`x`, :data:`y` and :data:`z`: the center of the tessellation or mesh (if both a tessellation and a mesh have been loaded, the mesh is considered).

  **Default value**: :data:`x:y:z`.

.. option:: -cameraangle <angle>

  Specify the opening angle of the camera along the horizontal direction (in degrees).

  The opening angle along the vertical direction is determined from the opening along the horizontal direction and the image size ratio.

  **Default value**: :data:`25`.

.. option:: -camerasky <dir_x>:<dir_y>:<dir_z>

  Specify the sky vector of the camera (vertical direction of the image).

  **Default value**: :data:`0:1:0` in 2D and :data:`0:0:1` in 3D.

.. option:: -cameraprojection <projection>

  Specify the type of projection of the camera, which can be :data:`perspective` or :data:`orthographic`.

  **Default value**: :data:`orthographic` for 2D and :data:`perspective` for 3D.

Scene Settings
~~~~~~~~~~~~~~

.. option:: -scenebackground <color>

  Specify the color of the background, which can be any color as described in :ref:`colors_and_color_maps`.

  **Default value**: :data:`white`.

.. option:: -sceneshadow <logical>

  Specify whether the scene should include shadows.

  **Default value**: :data:`0` in 2D and :data:`1` in 3D.

Output Image Settings
~~~~~~~~~~~~~~~~~~~~~

.. option:: -imagesize <size_x>,<size_y>

  Specify the size of the image (in pixels).

  **Default value**: :data:`1200:900`.

.. option:: -imageantialias <logical>

  Specify whether antialiasing (which produces a smoother image) should be used.

  **Default value**: :data:`1`.

.. option:: -imageformat <format1>,<format2>,...

  Specify the format(s) of the output image(s), which can be:

  - :data:`png`: the PNG format;
  - :data:`pov`: the POV-Ray format;
  - :data:`pov:objects`: the POV-Ray format, but containing only the objects (the resulting file can be loaded with :option:`-includepov`, not compatible with :data:`png`);
  - :data:`vtk`: the VTK format.

  **Default value**: :data:`png`.

Scripting
~~~~~~~~~

.. option:: -loop <variable> <initial_value> <increment_value> <final_value> <commands> -endloop

  Create a loop of commands, as in :data:`-loop Z 0.1 0.1 0.9 -slicemesh "z=Z" -print zZ -endloop`.

  **Default value**: -.

Output Options
~~~~~~~~~~~~~~

.. option:: -outdir <dir1>,<dir2>,...

  Specify the output directories (the first valid one is used), which can be:

  - a custom directory;
  - :data:`sim_dir`: the standard location of the simulation directory, :data:`<dir.sim>/images/<format>`, where :data:`<format>` is the image format (see option :option:`-imageformat`). :data:`sim_dir` is only valid if a simulation directory is loaded as input.

  For example, to write to a simulation directory when loaded as input and to the local directory in other cases, :data:`sim_dir,.` (which may be placed in the initialization file).

  **Default value**: :option:`.`.

Print Options
~~~~~~~~~~~~~

.. option:: -print <file_name>

  Print the image.  The file name should be extension free.

  **Default value**: -.

Advanced Options
~~~~~~~~~~~~~~~~

.. option:: -includepov <file_name1>[:<transformation1>:<transformation2>:...],<file_name2>,...

  Include objects to the image under the form of POV-Ray files and optionally apply it a transformation.  A transformation can be:

  - |translate|;
  - |scale|;
  - :data:`rotate(<theta_x>,<theta_y>,<theta_z>)`: rotate by angles :data:`thetax`, :data:`thetay` and :data:`thetaz` about :data:`x`, :data:`y` and :data:`z`.

    .. important:

    The rotation is read in POV-Ray style; i.e., according to the POV-Ray documentation::

      Note that the order of the rotations does matter.  Rotations occur about the x-axis
      first, then the y-axis, then the z-axis.  If you are not sure if this is what you
      want, then you should only rotate on one axis at a time using multiple rotation
      statements to get a correct rotation.  Rotation is always performed relative to the
      axis. Thus, if an object is some distance from the axis of rotation, it will not only
      rotate but it will orbit about the axis as though it was swinging around on an
      invisible string.  POV-Ray uses a left-handed rotation system. Using the famous
      "Computer Graphics Aerobics" exercise, you hold up your left hand and point your thumb
      in the positive direction of the axis of rotation.  Your fingers will curl in the
      positive direction of rotation.  Similarly, if you point your thumb in the negative
      direction of the axis, your fingers will curl in the negative direction of
      rotation.

  **Default value**: -.

Output Files
------------

- :file:`.png`: PNG file, a bitmapped image (the alpha channel is off);
- :file:`.pov`: POV-Ray file, a POV-Ray script file;
- :file:`.vtk`: a VTK file, for interactive visualization.

A PNG image can be obtained from a POV-Ray file by invoking POV-Ray as follows (see the POV-Ray documentation for details and further commands):

.. code-block:: console

  $ povray <file.pov> +W<image_width>+H<image_height> -D +A0.2

Examples
--------

Below are some examples of use of neper -V.

- Print out tessellation :file:`n10-id1.tess` with cells colored from their identifiers and an image size of 900 x 450 pixels:

  .. code-block:: console

    $ neper -V n10-id1.tess -datacellcol id -imagesize 900:450 -print img

- Print out tessellation :file:`n10-id1.tess` with cells colored from crystal orientations and semi-transparency:

  .. code-block:: console

    $ neper -V n10-id1.tess -datacellcol ori -datacelltrs 0.5 -print img

- Print out mesh :file:`n10-id1.msh` with elements colored from scalar values written in file :file:`v` and a scale ranging from 0 to 100:

  .. code-block:: console

    $ neper -V n10-id1.msh -dataeltcol "real:file(v)" -dataeltscale 0:100 -print img

- Print out mesh :file:`n10-id1.msh` with elements colored from nodal scalar values written in file :file:`v` and a scale ranging from 0 to 100:

  .. code-block:: console

    $ neper -V n10-id1.msh -datanodecol "real:file(v)" -dataeltcol from_nodes -dataeltscale 0:100 -print img

- Print out the 10 first cells of a 100-cell tessellation, colored from their identifiers and semi-transparency, and with edges shown in red and vertices shown as green spheres of radius 0.01:

  .. code-block:: console

    $ neper -V n100-id1.tess -showcell "id<=10" -datacellcol id -datacelltrs 0.5 -showedge cell_shown -showver cell_shown -dataverrad 0.01 -dataedgecol red -datavercol green -print img

- Print out the interior element sets of mesh :file:`n100-id1.msh` and show the 1D elements:

  .. code-block:: console

    $ neper -V n100-id1.tess,n100-id1.msh -dataelsetcol id -showelset 'body>0' -showelt1d elt3d_shown -print img

- Print out 3 slices of mesh :file:`n100-id1.msh`:

  .. code-block:: console

    $ neper -V n100-id1.msh -dataelsetcol id -slicemesh "x=0.5:y=0.5:z=0.5" -print img

- Print out slices of mesh :file:`n100-id1.msh`, at z coordinates ranging from 0.1 to 0.9 by step of 0.1, each slice being printed in a separate file:

  .. code-block:: console

    $ neper -V n100-id1.msh -dataelsetcol id -loop Z 0.1 0.1 0.9 -slicemesh "z=Z" -print imgZ -endloop

- Print out a deformed mesh colored by orientations, defined from a simulation directory:

  .. code-block:: console

    $ neper -V mysim.sim -simstep 10 -datanodecoo coo -dataeltcol ori -print img

- Print out a deformed mesh colored by orientations, defined from a simulation directory; generate an image at each deformation step:

  .. code-block:: console

    $ neper -V mysim.sim -loop STEP 0 1 10 -simstep STEP -datanodecoo coo -dataeltcol ori -print imgSTEP -endloop

.. [#space] It currently only affects the arguments of :option:`-datapointrad`.
