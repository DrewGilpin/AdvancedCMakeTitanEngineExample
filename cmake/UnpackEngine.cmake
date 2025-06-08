function(unpack_engine_files)
    set(base "${PROJECT_SOURCE_DIR}")
    set(assets_dir "${base}/assets")
    set(ee_dir "${base}/third_party/EE")

    # Engine.pak
    set(asset_zip "${assets_dir}/Engine.zip")
    set(asset_file "${assets_dir}/Engine.pak")
    if(NOT EXISTS "${asset_file}" AND EXISTS "${asset_zip}")
        message(STATUS "Extracting ${asset_zip}")
        file(ARCHIVE_EXTRACT INPUT "${asset_zip}" DESTINATION "${assets_dir}")
    endif()

    set(archives
        Engine.zip
        Engine64DX11.zip
        EngineDebug64DX11.zip
        EngineDebug64DX11_pdb.zip)
    set(outputs
        Engine.a
        Engine64DX11.lib
        EngineDebug64DX11.lib
        EngineDebug64DX11.pdb)

    list(LENGTH archives count)
    math(EXPR last_index "${count}-1")
    foreach(i RANGE 0 ${last_index})
        list(GET archives ${i} archive)
        list(GET outputs ${i} out_file)
        set(zip_path "${ee_dir}/${archive}")
        set(out_path "${ee_dir}/${out_file}")
        if(NOT EXISTS "${out_path}" AND EXISTS "${zip_path}")
            message(STATUS "Extracting ${archive}")
            file(ARCHIVE_EXTRACT INPUT "${zip_path}" DESTINATION "${ee_dir}")
        endif()
    endforeach()
endfunction()
