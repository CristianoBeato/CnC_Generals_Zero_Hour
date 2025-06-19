##############################################
##	Beato Command & Conquer Generals(tm)    ##
##############################################
## Game Device 
set( SDL3DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3BIGFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3BIGFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3BIGFileSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3BIGFileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3CDManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3CDManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3GameEngine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3LocalFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3LocalFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3LocalFileSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3LocalFileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/Common/SDL3OSDisplay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/GameClient/SDL3DIKeyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3DIKeyboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/GameClient/SDL3DIMouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3DIMouse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/SDL3Device/GameClient/SDL3Mouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3Mouse.h
    )

set( VIDEO_DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/VideoDevice/Bink/BinkVideoPlayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/VideoDevice/Bink/BinkVideoPlayer.h
    )

set( W3D_DEVICE_SOURCES 
    # Common
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/Common/W3DConvert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/Common/W3DConvert.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/Common/System/W3DFunctionLexicon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/Common/W3DFunctionLexicon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/Common/Thing/W3DModuleFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/Common/W3DModuleFactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/Common/System/W3DRadar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/Common/W3DRadar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/Common/Thing/W3DThingFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/Common/W3DThingFactory.h
    
    # GameClient
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/HeightMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/HeightMap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/TerrainTex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/TerrainTex.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/TileData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/TileData.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DAssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DAssetManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DAssetManagerExposed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DAssetManagerExposed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DBibBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DBibBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DBufferManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DCustomEdging.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DCustomEdging.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DCustomScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDebugDisplay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDebugDisplay.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDebugIcons.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDebugIcons.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDisplay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDisplay.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDisplayString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDisplayString.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDisplayStringManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDisplayStringManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DDynamicLight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DDynamicLight.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DFileSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DFileSystem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGadget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DGameClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGameClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGameFont.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGameWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGameWindowManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DGranny.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGranny.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DInGameUI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DInGameUI.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DGUICallbacks.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DMirror.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DMouse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DMouse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DParticleSys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DParticleSys.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DPoly.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DPoly.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DRoadBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DScene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DShadow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DShaderManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DShaderManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DShroud.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DShroud.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DStatusCircle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DStatusCircle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DProjectedShadow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DTerrainTracks.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DTerrainVisual.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DTreeBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DVideoBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DVideobuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DView.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DVolumetricShadow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DWater.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DWaterTracks.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3dWaypointBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DWaypointBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/W3DWebBrowser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/W3DWebBrowser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/WorldHeightMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/WorldHeightMap.h

    # GameClient Module
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DDebrisDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DDefaultDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DDependencyModelDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DLaserDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DOverlordTankDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DPoliceCarDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DProjectileStreamDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DScienceModelDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DTankTruckDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DTracerDraw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h

    # GameClient Drawable Draw
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DDependencyModelDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DOverlordTankDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DPoliceCarDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DProjectileStreamDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DScienceModelDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DTracerDraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDraw.cpp

    # GameClient GUI
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/W3DGameFont.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/W3DGameWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/W3DGameWindowManager.cpp
    
    # GameClient GUI Gadget
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DCheckBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DComboBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DHorizontalSlider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DListBox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DProgressBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DPushButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DRadioButton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DStaticText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DTabControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DTextEntry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/Gadget/W3DVerticalSlider.cpp

    # GameClient GUI GUICallbacks
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DControlBar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DMainMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DMOTD.cpp

    # GameLogic
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameLogic/W3DGameLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameLogic/W3DGameLogic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameLogic/W3DGhostObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameLogic/W3DGhostObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/W3DDevice/GameLogic/W3DTerrainLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/W3DDevice/GameLogic/W3DTerrainLogic.h
    )

set( ENGINE_DEVICES_SOURCES_ALL 
    ${SDL3DEVICE_SOURCES}
    ${VIDEO_DEVICE_SOURCES}
    ${W3D_DEVICE_SOURCES}
    )

add_library( GameEngineDevice STATIC ${ENGINE_DEVICES_SOURCES_ALL} )
add_dependencies( GameEngineDevice WWVegas )
#target_include_directories( GameEngineDevice PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/Include )
target_precompile_headers( GameEngineDevice 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/GameEngine/Include/Precompiled/PreRTS.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/Common/SDL3GameEngine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3DIKeyboard.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3DIMouse.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/SDL3Device/GameClient/SDL3Mouse.h
)