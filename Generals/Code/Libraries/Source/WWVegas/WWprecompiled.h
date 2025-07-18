/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /WWvegas/WWprecompiled.h                                    $*
 *                                                                                             *
 *              Original Author:: Cristiano Beato                                              *
 *                                                                                             *
 *                      $Author:: Vss_sync                                                    $*
 *                                                                                             *
 *                     $Modtime:: 6/21/25 8:51a                                               $*
 *                                                                                             *
 *                    $Revision:: 00                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef __WWPRECOMPILED_H__
#define __WWPRECOMPILED_H__

//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cstdarg>
#include <filesystem>
#include <cmath>
#include <new>
#include <algorithm>
#include <limits.h> 
#include <float.h>
#include <assert.h>
#include <memory.h>
#include <errno.h>
#include <sys/stat.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_timer.h>

#include <SDL3/SDL_mutex.hpp>
#include <SDL3/SDL_thread.hpp>

// WWLib common utilities lib 
#include "WWLib/always.h"
#include "WWLib/argv.h"
#include "WWLib/b64pipe.h"
#include "WWLib/b64straw.h"
#include "WWLib/base64.h"
#include "WWLib/bfiofile.h"
#include "WWLib/binheap.h"
#include "WWLib/bittype.h"
#include "WWLib/blitblit.h"
#include "WWLib/blit.h"
#include "WWLib/blitter.h"
#include "WWLib/blowfish.h"
#include "WWLib/blowpipe.h"
#include "WWLib/blwstraw.h"
//#include "WWLib/bool.h"
#include "WWLib/borlandc.h"
#include "WWLib/bound.h"
#include "WWLib/bsurface.h"
#include "WWLib/bufffile.h"
#include "WWLib/CallbackHook.h"
#include "WWLib/chunkio.h"
#include "WWLib/_convert.h"
#include "WWLib/Convert.h"
#include "WWLib/cpudetect.h"
#include "WWLib/crcpipe.h"
#include "WWLib/crcstraw.h"
#include "WWLib/cstraw.h"
#include "WWLib/data.h"
#include "WWLib/dib.h"
#include "WWLib/draw.h"
#include "WWLib/dsurface.h"
#include "WWLib/ffactory.h"
#include "WWLib/fixed.h"
#include "WWLib/gcd_lcm.h"
#include "WWLib/hashcalc.h"
#include "WWLib/hash.h"
#include "WWLib/hashtab.h"
#include "WWLib/hashtemplate.h"
#include "WWLib/hsv.h"
#include "WWLib/incdec.h"
#include "WWLib/inisup.h"
#include "WWLib/iostruct.h"
#include "WWLib/keyboard.h"
#include "WWLib/LaunchWeb.h"
#include "WWLib/lcwpipe.h"
#include "WWLib/mempool.h"
#include "WWLib/misc.h"
#include "WWLib/mixfile.h"
#include "WWLib/mmsys.h"
#include "WWLib/_mono.h"
#include "WWLib/msgloop.h"
#include "WWLib/multilist.h"
#include "WWLib/mutex.h"
#include "WWLib/noinit.h"
#include "WWLib/Notify.h"
#include "WWLib/nstrdup.h"
#include "WWLib/ntree.h"
#include "WWLib/obscure.h"
#include "WWLib/pkpipe.h"
#include "WWLib/pkstraw.h"
#include "WWLib/Point.h"
#include "WWLib/rc4.h"
#include "WWLib/rcfile.h"
#include "WWLib/readline.h"
#include "WWLib/realcrc.h"
#include "WWLib/refcount.h"
#include "WWLib/ref_ptr.h"
#include "WWLib/registry.h"
#include "WWLib/rlerle.h"
#include "WWLib/rndstrng.h"
#include "WWLib/rng.h"
#include "WWLib/rsacrypt.h"
#include "WWLib/sampler.h"
#include "WWLib/search.h"
#include "WWLib/sha.h"
#include "WWLib/shapeset.h"
#include "WWLib/shapipe.h"
#include "WWLib/sharebuf.h"
#include "WWLib/shastraw.h"
#include "WWLib/Signaler.h"
#include "WWLib/simplevec.h"
#include "WWLib/slist.h"
#include "WWLib/slnode.h"
#include "WWLib/smartptr.h"
#include "WWLib/srandom.h"
#include "WWLib/stimer.h"
#include "WWLib/stl.h"
#include "WWLib/strtok_r.h"
#include "WWLib/Surface.h"
#include "WWLib/surfrect.h"
#include "WWLib/swap.h"
#include "WWLib/systimer.h"
#include "WWLib/TagBlock.h"
#include "WWLib/textfile.h"
#include "WWLib/thread.h"
#include "WWLib/_timer.h"
#include "WWLib/timer.h"
#include "WWLib/trackwin.h"
#include "WWLib/trackxy.h"
#include "WWLib/trect.h"
#include "WWLib/trim.h"
#include "WWLib/uarray.h"
#include "WWLib/verchk.h"
#include "WWLib/visualc.h"
#include "WWLib/widestring.h"
#include "WWLib/plat.h"
#include "WWLib/WWCOMUtil.h"
#include "WWLib/wwfile.h"
#include "WWLib/wwfont.h"
#include "WWLib/wwmouse.h"
#include "WWLib/wwstring.h"
#include "WWLib/_xmouse.h"
#include "WWLib/xmouse.h"
#include "WWLib/xsurface.h"

// WWDebug
#include "WWDebug/wwdebug.h"
#include "WWDebug/wwhack.h"
#include "WWDebug/wwmemlog.h"
#include "WWDebug/wwprofile.h"

// WWMath Math utils 
#include "WWMath/aabox.h"
#include "WWMath/aabtreecull.h"
#include "WWMath/aaplane.h"
#include "WWMath/cardinalspline.h"
#include "WWMath/castres.h"
#include "WWMath/catmullromspline.h"
#include "WWMath/colmathaabox.h"
#include "WWMath/colmathfrustum.h"
#include "WWMath/colmath.h"
#include "WWMath/colmathinlines.h"
#include "WWMath/colmathline.h"
#include "WWMath/colmathplane.h"
#include "WWMath/cullsys.h"
#include "WWMath/culltype.h"
#include "WWMath/curve.h"
#include "WWMath/euler.h"
#include "WWMath/frustum.h"
#include "WWMath/gridcull.h"
#include "WWMath/hermitespline.h"
#include "WWMath/lineseg.h"
#include "WWMath/lookuptable.h"
#include "WWMath/matrix3d.h"
#include "WWMath/matrix3.h"
#include "WWMath/matrix4.h"
#include "WWMath/obbox.h"
#include "WWMath/ode.h"
#include "WWMath/plane.h"
#include "WWMath/pot.h"
#include "WWMath/quat.h"
#include "WWMath/rect.h"
#include "WWMath/sphere.h"
#include "WWMath/tcbspline.h"
#include "WWMath/tri.h"
#include "WWMath/v3_rnd.h"
#include "WWMath/vector2.h"
#include "WWMath/vector2i.h"
#include "WWMath/vector3.h"
#include "WWMath/Vector3i.h"
#include "WWMath/vector4.h"
#include "WWMath/vehiclecurve.h"
#include "WWMath/vp.h"
#include "WWMath/wwmath.h"
#include "WWMath/wwmathids.h"

// WW3D2 3d rendering lib
#include "WW3D2/aabtreebuilder.h"
#include "WW3D2/aabtree.h"
#include "WW3D2/agg_def.h"
#include "WW3D2/animobj.h"
#include "WW3D2/assetmgr.h"
#include "WW3D2/bitmaphandler.h"
#include "WW3D2/bmp2d.h"
#include "WW3D2/boxrobj.h"
#include "WW3D2/bw_render.h"
#include "WW3D2/bwrender.h"
#include "WW3D2/camera.h"
#include "WW3D2/classid.h"
#include "WW3D2/collect.h"
#include "WW3D2/colorspace.h"
#include "WW3D2/coltest.h"
#include "WW3D2/coltype.h"
#include "WW3D2/composite.h"
#include "WW3D2/dazzle.h"
#include "WW3D2/ddsfile.h"
#include "WW3D2/decalmsh.h"
#include "WW3D2/decalsys.h"
#include "WW3D2/distlod.h"
#include "WW3D2/dllist.h"
#include "WW3D2/dynamesh.h"
#include "WW3D2/font3d.h"
#include "WW3D2/formconv.h"
#include "WW3D2/framgrab.h"
#include "WW3D2/hanim.h"
#include "WW3D2/hanimmgr.h"
#include "WW3D2/hcanim.h"
#include "WW3D2/hlod.h"
#include "WW3D2/hmorphanim.h"
#include "WW3D2/hrawanim.h"
#include "WW3D2/htree.h"
#include "WW3D2/htreemgr.h"
#include "WW3D2/intersec.h"
#include "WW3D2/inttest.h"
#include "WW3D2/layer.h"
#include "WW3D2/lightenvironment.h"
#include "WW3D2/light.h"
#include "WW3D2/line3d.h"
#include "WW3D2/mapper.h"
#include "WW3D2/matinfo.h"
#include "WW3D2/matpass.h"
#include "WW3D2/matrixmapper.h"
#include "WW3D2/meshbuild.h"
#include "WW3D2/meshdam.h"
#include "WW3D2/meshgeometry.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmatdesc.h"
#include "WW3D2/meshmdl.h"
#include "WW3D2/metalmap.h"
#include "WW3D2/missingtexture.h"
#include "WW3D2/motchan.h"
#include "WW3D2/nullrobj.h"
#include "WW3D2/part_buf.h"
#include "WW3D2/part_emt.h"
#include "WW3D2/part_ldr.h"
#include "WW3D2/pivot.h"
#include "WW3D2/pointgr.h"
#include "WW3D2/polyinfo.h"
#include "WW3D2/predlod.h"
#include "WW3D2/prim_anim.h"
#include "WW3D2/projector.h"
#include "WW3D2/proto.h"
#include "WW3D2/proxy.h"
#include "WW3D2/rddesc.h"
#include "WW3D2/render2d.h"
#include "WW3D2/render2dsentence.h"
#include "WW3D2/renderobjectrecycler.h"
#include "WW3D2/rendobj.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/ringobj.h"
#include "WW3D2/robjlist.h"
#include "WW3D2/scene.h"
#include "WW3D2/segline.h"
#include "WW3D2/seglinerenderer.h"
#include "WW3D2/shader.h"
#include "WW3D2/shattersystem.h"
#include "WW3D2/snapPts.h"
#include "WW3D2/sortingrenderer.h"
#include "WW3D2/soundrobj.h"
#include "WW3D2/sphereobj.h"
#include "WW3D2/sr_util.h"
#include "WW3D2/statistics.h"
#include "WW3D2/streak.h"
#include "WW3D2/streakRender.h"
#include "WW3D2/stripoptimizer.h"
#include "WW3D2/surfaceclass.h"
#include "WW3D2/texfcach.h"
#include "WW3D2/texproject.h"
#include "WW3D2/textdraw.h"
#include "WW3D2/texturefile.h"
#include "WW3D2/texture.h"
#include "WW3D2/textureloader.h"
#include "WW3D2/texturethumbnail.h"
#include "WW3D2/txt2d.h"
#include "WW3D2/txt.h"
#include "WW3D2/vertmaterial.h"
#include "WW3D2/visrasterizer.h"
#include "WW3D2/w3d_dep.h"
#include "WW3D2/w3derr.h"
#include "WW3D2/w3dexclusionlist.h"
#include "WW3D2/w3d_file.h"
#include "WW3D2/w3d_obsolete.h"
#include "WW3D2/w3d_util.h"
#include "WW3D2/ww3dformat.h"
#include "WW3D2/ww3d.h"
#include "WW3D2/ww3dids.h"
#include "WW3D2/ww3dtrig.h"

#ifdef ENABLE_USE_DX8
#include "WW3D2/DirectX/dx8caps.h"
#include "WW3D2/DirectX/dx8fvf.h"
#include "WW3D2/DirectX/dx8indexbuffer.h"
#include "WW3D2/DirectX/dx8list.h"
#include "WW3D2/DirectX/dx8polygonrenderer.h"
#include "WW3D2/DirectX/dx8renderer.h"
#include "WW3D2/DirectX/dx8texman.h"
#include "WW3D2/DirectX/dx8vertexbuffer.h"
#include "WW3D2/DirectX/dx8webbrowser.h"
#include "WW3D2/DirectX/dx8wrapper.h"
#endif //ENABLE_USE_DX8

#ifdef ENABLE_USE_OPENGL
#include "WW3D2/OpenGL/OpenGLwrapper.h"
#endif //ENABLE_USE_OPENGL

// WWAudio
#include "WWAudio/AABTreeSoundCullClass.h"
#include "WWAudio/AudibleSound.h"
#include "WWAudio/AudioEvents.h"
#include "WWAudio/AudioSaveLoad.h"
#include "WWAudio/FilteredSound.h"
#include "WWAudio/Listener.h"
#include "WWAudio/listenerhandle.h"
#include "WWAudio/LogicalListener.h"
#include "WWAudio/LogicalSound.h"
#include "WWAudio/PriorityVector.h"
#include "WWAudio/sound2dhandle.h"
#include "WWAudio/Sound3D.h"
#include "WWAudio/sound3dhandle.h"
#include "WWAudio/SoundBuffer.h"
#include "WWAudio/SoundChunkIDs.h"
#include "WWAudio/SoundCullObj.h"
#include "WWAudio/soundhandle.h"
#include "WWAudio/SoundPseudo3D.h"
#include "WWAudio/SoundScene.h"
#include "WWAudio/SoundSceneObj.h"
#include "WWAudio/soundstreamhandle.h"
#include "WWAudio/Threads.h"
#include "WWAudio/Utils.h"
#include "WWAudio/WWAudio.h"

// WWDownload
#include "WWDownload/DownloadDebug.h"
#include "WWDownload/downloaddefs.h"
#include "WWDownload/Download.h"
#include "WWDownload/ftpdefs.h"
#include "WWDownload/ftp.h"
#include "WWDownload/Registry.h"
#include "WWDownload/urlBuilder.h"


#endif //__WWPRECOMPILED_H__