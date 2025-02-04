.. _introduction:

Introduction
============

Description
-----------

Neper is a software package for polycrystal generation and meshing.  The polycrystals can be 2D or 3D. Neper is built around four modules:

*Module -T* generates polycrystals as tessellations.  The tessellations can be *(i)* standard tessellations (Voronoi, etc.) or tessellations generated from cell properties (e.g. a size distribution), or *(ii)* multiscale tessellations, which are characterized by cell subdivision and are able to represent more complex microstructures.  All capabilities available for standard tessellations are also available for multiscale tessellations.  Tessellations with a very wide variety of cells morphologies can be generated, with the limitations that cells are convex.  Once generated, the tessellations can be *regularized* by removing their smallest features (edges and faces), which then enables good-quality meshing.  Periodicity conditions can be prescribed.  Crystal orientations are provided for the cells.  The output is a *tessellation file* written at a scalar (vectorial), :file:`.tess`, or raster format, :file:`.tesr`.  Scalar tessellations can be meshed by module -M while raster tessellations can typically be used by FFT solvers.

*Module -M* meshes polycrystals described as tessellation files (:file:`.tess` and 2D :file:`.tesr`). Two meshing techniques are available: *free* (or *unstructured*) meshing, which generates triangular elements (in 2D) or tetrahedral elements (in 3D) that follow the grain shapes, and *mapped* (or *structured*) meshing, which generates regular square elements (in 2D) or regular cubic elements (in 3D) that do not necessarily follow the grain shapes.  Free meshing into good-quality elements is ensured by optimized meshing rules, and multimeshing---a complementary use of several meshing algorithms.  Remeshing is also available and is similar to meshing except that it takes a mesh as input.  Cohesive elements can be inserted at interfaces.  The output is a *mesh file* written at the :file:`.msh` format, which can be readily be used as input by Neper's companion program, `FEPX <https://fepx.info>`_, or other formats.

*Module -S* processes simulation results from FEPX.  It translates the FEPX raw simulation results into a more friendly *simulation directory* :file:`.sim`, and includes various post-processing capabilities to compute new results. The *simulation directory* can be used as such and loaded by module -V for result visualization.

*Module -V* generates publication-quality PNG images or VTK files of tessellations, meshes and simulation results.  The results can be defined from internal data, data loaded from external files, or a simulation directory as generated by module -S.  The output PNG images can be highly parameterized, with custom colors and transparency for the different entities, slices, etc., and is generated by ray tracing (using POV-Ray),  while the output VTK file can be used for interactive visualization (e.g., using Paraview).

Neper strives to be an easy-to-use, efficient and robust tool.  All the input data are prescribed non-interactively, using command lines and / or ASCII files, so that all treatments can be automated.

Resources and Support
---------------------

Several, complementary resources describing Neper are available:

- The Neper reference manual, which is this document, describes all Neper's capabilities.

- The `Neper website <https://neper.info>`_ gives a general introduction to Neper and is where Neper can be downloaded from.  Official versions are released every few months.

- The `Neper GitHub repository <https://github.com/rquey/neper>`_ is where the latest, continuous-integration version is available and where user interactions take place:

  - To get the code, clone the repository using:

    .. code-block:: console

      $ git clone https://github.com/rquey/neper.git

    which gives access to the latest stable development release on the default, :code:`main` branch. To update the code, run :command:`git pull` from within the repository.

  - To report bugs or request new features, use the `issue tracker <https://github.com/rquey/neper/issues>`_.

  - To ask questions or share comments, use the `discussion forum <https://github.com/rquey/neper/discussions>`_.

- The three Neper reference papers:

  - `R. Quey, P.R. Dawson and F. Barbe, Large-scale 3D random polycrystals for the finite element method: Generation, meshing and remeshing, Comput. Methods Appl. Mech. Engrg., vol. 200, pp. 1729-1745, 2011, <https://neper.info/docs/neper-reference-paper.pdf>`_ describes the regularization and meshing methodologies;

  - `R. Quey and L. Renversade, Optimal polyhedral description of 3D polycrystals: Method and application to statistical and synchrotron X-ray diffraction data, Comput. Methods Appl. Mech. Engrg., vol. 330, pp. 308-333, 2018, <https://doi.org/10.1016/j.cma.2017.10.029>`_ describes tessellation generation from experimental properties;

  - `R. Quey, A. Villani and C. Maurice, Nearly uniform sampling of crystal orientations, J. Appl. Crystallogr., vol. 51, pp. 1162-1173, 2018, <https://doi.org/10.1107/S1600576718009019>`_ describes uniform sampling of crystal orientations.

Resources for FEPX can be accessed from https://fepx.info.

Installing Neper
----------------

Neper is written in (mostly ANSI) C and a little C++, and it can run on any Unix-like system (including MacOS).  Neper also runs on Microsoft Windows using the Windows subsystem for Linux (WSL), the Ubuntu app or similar solutions, although we do not test nor support this usage and multithreading must be turned off (which slows down execution significantly).  Multithreading of the code is achieved via `OpenMP <https://www.openmp.org/>`_ and operates on all threads (the actual number of threads can be set throught the :code:`OMP_NUM_THREADS` environment variable).  Compilation is performed via `CMake <https://cmake.org>`_:

- Create a :file:`build` directory, for instance as a subdirectory of Neper's :file:`src` directory:

  .. code-block:: console

    $ cd src
    $ mkdir build

- Run CMake from within the :file:`build` directory, pointing to Neper's :file:`src` directory:

  .. code-block:: console

    $ cd build
    $ cmake ..    (on Windows: cmake -DHAVE_OPENMP=OFF ..)

- Build Neper:

  .. code-block:: console

    $ make

  Use option :data:`-j` for a multithreaded compilation.

- Install Neper on your system (as root):

  .. code-block:: console

    $ make install

.. _have_dependency:

This procedure uses the default configuration options and should work out-of-the-box if the required dependencies are available in standard system locations.  If needed, a finer configuration of which dependencies are included can be achieved, before building Neper, by setting variables :code:`HAVE_<DEPENDENCY>`.  This can be done using

.. code-block:: console

  $ ccmake ..

for an interactive command-line tool, or

.. code-block:: console

  $ cmake-gui ..

for an interactive graphical tool, or directly at the command line, using Cmake's :data:`-D` option:

.. code-block:: console

  $ cmake -DHAVE_<DEPENDENCY1>={ON,OFF} -DHAVE_<DEPENDENCY2>={ON,OFF} ..

The dependencies which are (optionally) necessary at compilation time and must be (optionally) installed on your system before Neper is compiled are the following:


- The `GNU Scientific Library <https://www.gnu.org/software/gsl>`_ (GSL, mandatory, variable :code:`HAVE_GSL`).  It is likely to be available on your system or from your system package manager (binary and development packages); alternatively, the source code version can be downloaded from the program website.

- The `OpenMP <https://www.openmp.org/>`_ library (optional but highly-recommended, enabled by default, variable :code:`HAVE_OPENMP`).  It is likely to be available on your system or from your system package manager. [#mac-install]_

- The pthread library (mandatory). It is likely to be available on your system or from your system package manager.

Other dependencies are only needed at run-time (they are not necessary for compilation):

- The `Gmsh <https://gmsh.info>`_ program (version 2.4.2 or higher, excluding version 2.5.1, mandatory for module -M). Both binary and source-code versions can be downloaded from the program website (compiling from the source code significantly speeds up meshing).  Gmsh must be available at the terminal as the command :program:`gmsh`, or the path to its binary must be specified with option :option:`-gmsh` (in module -M).

- The `POV-Ray <http://www.povray.org>`_ program (version 3.7 or higher, mandatory for module -V).  It is likely to be available on your system or from your system package manager (binary package); alternatively, a binary, or the source code, can be downloaded the program website.  POV-Ray must be available at the terminal as the command :program:`povray`, or the path to its binary must be specified with option :option:`-povray` (in module -V).

Other third-party libraries are directly included in the source code (see directory :file:`src/contrib`) and are not dependencies *per se*:

- The `NLopt <https://nlopt.readthedocs.io>`_ library.  If it is already available on your system, the system version will be used instead.  To force the use of the built-in version, set :code:`FORCE_BUILTIN_NLOPT` to :code:`ON` (default :code:`OFF`) as described :ref:`previously <have_dependency>` for :code:`HAVE_<DEPENDENCY>`.

- The `libscotch <https://www.labri.fr/perso/pelegrin/scotch>`_ library. If it is already available on your system, the system version will be used instead.  To force the use of the built-in version, set :code:`FORCE_BUILTIN_LIBSCOTCH` to :code:`ON` (default :code:`OFF`) as described :ref:`previously <have_dependency>` for :code:`HAVE_<DEPENDENCY>`.

- The `tinycolormap <https://github.com/yuki-koyama/tinycolormap>`_ library.

- The `nanoflann <https://github.com/jlblancoc/nanoflann>`_ library.

- The `muparser <https://beltoforion.de/en/muparser>`_ library.

- The `openGJK <https://github.com/MattiaMontanari/openGJK>`_ library.

Testing Neper
-------------

Neper comes packaged with tests and reference outputs. To run the tests, execute the following from your build folder:

.. code-block:: console

  $ make test

or (equivalently):

.. code-block:: console

  $ ctest

This runs the tests in :code:`Normal` mode, for which the produced output files are compared to reference ones. The (packaged) reference output files are generated on Ubuntu 20.04, using compiler GCC 9.3.0, (built-in) NLopt 2.6.1, (built-in) libscotch 6.0, Gmsh 4.9.4 and POV-Ray 3.7.0. It is expected that different versions may result in minor (insignificant) changes to the output, though this will generally result in failed tests.  If this happens, you may switch to the :code:`Minimal` mode as described in the following.

The testing mode is controlled by variable :code:`BUILD_TESTING_MODE`, which may be changed as described :ref:`previously <have_dependency>` for :code:`HAVE_<DEPENDENCY>`.

- The (default) :code:`Normal` mode checks if the program completes without error and if the produced output is the same as a set of reference output.

- The :code:`Minimal` mode only checks if the program completes without error. This mode may be useful when installing on a machine which has program or library versions different from the ones with which the reference output was generated.

- The :code:`Writing` mode overwrites the reference outputs with the generated output.  This mode may be useful when installing on a machine which has program or library versions different from the ones with which the reference output was generated and the user needs a reference output before making changes to the source code.

Getting Started
---------------

The :program:`neper` binary must be run in a terminal, followed by a list of arguments:

.. code-block:: console

  $ neper <arguments>

Neper returns messages in the terminal and results in ASCII (optionally binary) files.

The list of arguments describes the problem to solve.  There are several
general-purpose, self-explanatory arguments:

.. code-block:: console

  $ neper --help
  $ neper --version
  $ neper --license

The following of this section provides information on how to call Neper's modules,
properly format option arguments and set up an initialization file.

Modules
~~~~~~~

To call a module, run:

.. code-block:: console

  $ neper <module_name> <module_arguments>

where the module name can be :data:`-T`, :data:`-M`, :data:`-S` or :data:`-V`, and the module arguments can include both required input data and options.  Input data (when not a file name) and options start by :data:`-`.  Options can be provided in arbitrary order and are always followed by a single argument.
String completion is available for all options, so they may be abbreviated as long as the abbreviation is not ambiguous. For instance, in module :data:`-T`, option :option:`-regularization` can be abbreviated to :data:`-reg`. Autocomplete is also available and will complete an option name (or provide possibilities for the option name) when hitting the :code:`Tab` key. For instance, :data:`-reg\<tab\>` completes to :data:`-regularization`, and :data:`neper -T -n 1 -d<tab>` shows :data:`-domain -dim`.

.. important::

  - An argument must not contain any spaces.

  - When an argument contains shell metacharacters (:data:`(`, :data:`)`, :data:`?`, :data:`<`, etc.), it must be enclosed in either single (:data:`'`) or double (:data:`"`) quotes to be read in properly.  (Only double quotes enable variable substitution by the shell).

Logical options can be enabled or disabled by providing argument values of :data:`1` or :data:`0`, respectively.  Integer or real arguments can be written as numeral values or :ref:`mathematical_and_logical_expressions`.  For instance, in module -T, option :data:`-rcl 0.5` can also be written as :data:`-rcl 1/2` or :data:`-rcl "cos(pi/3)"`.  For some options, different values can be specified to different entities by loading them from an external :ref:`data_file` (or similar), using :data:`file(<file_name>)`.  For the more complex case of a multiscale tessellation, a :ref:`multiscale_cell_file` can also be used, and loaded using :data:`msfile(<file_name>)`.

Module -V shows some exceptions with respect to these rules: the argument cannot be listed in arbitrary order, string completion is not available, and option :option:`-loop` takes several arguments.

Argument Separators
~~~~~~~~~~~~~~~~~~~

Some options may take several argument values, which can be combined using *separators*:

- The :data:`,` separator is used to combine uncorrelated arguments, i.e. arguments of the same type, which can be processed independently from each other, in any order.  This is for example the case of output file formats.

- The :data:`:` separator is used to combine correlated arguments, i.e. arguments of different types, which cannot be processed independently from each other and must be processed in order.  This is for example the case of the values of a variable in different directions.

- The :data:`::` separator is used in module -T (and a little in module -M) to assign argument values to the different scales of a multiscale tessellation.  It is a *super-separator* that takes precedence over the :data:`,` and :data:`:` standard separators.

Initialization File
~~~~~~~~~~~~~~~~~~~

.. index::

   --rcfile, initialization file

When Neper is run, it starts by reading commands from an initialization file, :file:`$HOME/.neperrc`, if that file exists.  Another initialization file can be specified with option :data:`--rcfile`, before calling a module:

.. code-block:: console

  $ neper --rcfile <my_rc_file> <module_name> <module_arguments>

The reading of an initialization file can be disabled using option :data:`--rcfile none`.

When a Neper module is called, Neper looks for the occurrence of :data:`neper \<module_name\>` in the initialization file and then reads all arguments until the next occurrence of :data:`neper` (which should denote the beginning of another module option field) or the end of the file.  The arguments may be any legal arguments but are typically limited to frequently-used options.  Moreover, any field of comments can be preceded by :data:`neper comments`.

Here is the example of an initialization file, featuring its syntax (parts beginning with :data:`##` do not belong to the file):

.. code-block:: plain

    neper comments -------------------------------------  ## comment
    This is my initialization file.                       ## comment
                                                          ## comment
            It is pretty incomplete though...             ## comment
                                                          ## comment
    neper -T -reg 1                                       ## -T option
    neper -M -gmsh my_gmsh_path                           ## -M option
         -order 2                                         ## -M option
                                                          ## comment
    neper comments                                        ## comment
            Remember to add what I do not remember!       ## comment
    neper -V -povray my_povray_path                       ## -V option
    neper comments -------------------------------------  ## comment

If the initialization file is not found, or if :data:`neper \<module_name\>` is not found inside it, Neper will consider only the command line arguments.  Also, if an argument is initialized several times (for instance, both in the initialization file and at the command line), only the last specified value is used.

Conventions used in this manual
-------------------------------

.. index::

   single: dollar sign $, shell prompt

- A command entered at the terminal is shown like this:

  .. code-block:: console

    $ command

  The first character on the line is the terminal prompt, and should not be typed. The dollar sign, :data:`$`, is used as the standard prompt in this manual, although some systems may use a different character.

- A program (or command) option is printed like :data:`this`;
- An option argument is printed like :data:`<this>`;
- The name of a variable, or a meta-syntactic variable, is printed like :data:`<this>`;
- A series of values are enclosed in curly brackets (:data:`{` and :data:`}`) and separated by :data:`,`, as in :data:`{1,3}`;
- A range of integer values or letters are enclosed in curly brackets (:data:`{` and :data:`}`) and separated by :data:`-`, as in :data:`{1-3}`;
- Mutually exclusive values are enclosed in curly brackets (:data:`{` and :data:`}`) and separated by :data:`|`, as in :data:`{possibility1|possibility2}`;
- Optional arguments are enclosed in square brackets (:data:`[` and :data:`]`);
- Different possibilities for an integer number, in a variable name, file name, etc. are printed using the :data:`#` symbol (e.g., one (or all) of :data:`<var1>`, :data:`<var2>`, etc. is printed :data:`<var#>`);
- An arbitrary piece of text, composed or zero or more characters, is printed using the :data:`*` symbol (as in the Shell language);
- Literal examples are printed like

  .. code-block:: console

    this

- File names are printed like :file:`this`.

Options that are only of secondary importance or for fine tuning are tagged :data:`(Secondary option)`.

Some options, such as :data:`-datacellcol`, :data:`-datafacecol`, etc., differ only by the fact that they apply to different entities and are documented together, as :data:`-data{cell,...,face,...}col`.

Some abbreviations are used consistently for options and contribute to Neper's
jargon:

================ =================================
**Abbreviation** **Meaning**
:code:`algo` 	 algorithm
:code:`arch` 	 architecture
:code:`aspratio` aspect ratio
:code:`cl`   	 characteristic length
:code:`col` 	 color or column
:code:`conv`	 convergence
:code:`coo`	 coordinate
:code:`crysym`   crystal symmetry
:code:`csys`	 coordinate system
:code:`diameq`   equivalent diameter
:code:`dim`  	 dimension
:code:`dis`  	 distribution or distortion
:code:`dof`	 degree of freedom
:code:`dup`	 duplicate(d)
:code:`elset` 	 element set
:code:`elt`   	 element
:code:`expr`  	 expression
:code:`<fact>` 	 factor
:code:`faset` 	 element face set
:code:`geo`   	 geometry
:code:`id`    	 identifier
:code:`ini` 	 initial
:code:`inf` 	 infinity
:code:`inter` 	 interpolation
:code:`iter`  	 iteration
:code:`<max>`   	 maximum
:code:`<min>`   	 minimum
:code:`morpho` 	 morphology
:code:`nb` 	 number
:code:`neigh` 	 neighbor
:code:`nset`  	 node set
:code:`opti` 	 optimization
:code:`ori`   	 orientation
:code:`part`  	 partition
:code:`poly`  	 polyhedron
:code:`pov` 	 POV-Ray file
:code:`qual`  	 quality
:code:`<rad>` 	 radius
:code:`rcl` 	 relative characteristic length
:code:`<res>` 	 resolution
:code:`rmax`   	 relative maximum
:code:`sing` 	 singular
:code:`stat`  	 statistics
:code:`surf`  	 surface
:code:`tesr`  	 raster tessellation
:code:`tess`  	 scalar tessellation
:code:`tmp`   	 temporary
:code:`trs` 	 transparency
:code:`val`   	 value
:code:`var`   	 variable
:code:`ver`   	 vertex
================ =================================

.. [#mac-install] On Mac, install :program:`llvm` and :program:`libomp` via Homebrew.

