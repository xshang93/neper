# This file is part of the Neper software package.
# Copyright(C) 2003-2022, Romain Quey.
# See the COPYING file in the top-level directory.

set (test_command -M -loadmesh n2-id1.msh -statnode id,x,y,z,dim,2dmeshp,2dmeshd,2dmeshv,2dmeshn -o test)
include(../../test.cmake)
