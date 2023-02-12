get_filename_component(CURRENT_DIR "." REALPATH)

set(TS3_SDK_VERSION 3.1.1.0 CACHE STRING "TeamSpeak SDK Version." FORCE)
set(TS3_SDK_SHA256  "ed4f4be03fa41e60f0a6c2d1f531566ef0b352932d34808195bb1bb7fc046987" CACHE STRING "TeamSpeak SDK File SHA256." FORCE)
set(DOWNLOAD_URL    "https://files.teamspeak-services.com/releases/sdk/${TS3_SDK_VERSION}/ts3_sdk_${TS3_SDK_VERSION}.zip")
set(DOWNLOAD_OUTPUT "${CURRENT_DIR}/ts3_sdk_${TS3_SDK_VERSION}.zip")

function(download_file)
  message(STATUS "[Downloading] ${DOWNLOAD_URL} -> ${DOWNLOAD_OUTPUT}")
  file(DOWNLOAD "${DOWNLOAD_URL}" "${DOWNLOAD_OUTPUT}"
    SHOW_PROGRESS
    EXPECTED_HASH SHA256=${TS3_SDK_SHA256}
    TIMEOUT 10000
    INACTIVITY_TIMEOUT 10000
    TLS_VERIFY ON
    STATUS DOWNLOAD_STATE
  )
  list(GET DOWNLOAD_STATE 0 DOWNLOAD_STATE_CODE)
  list(GET DOWNLOAD_STATE 1 DOWNLOAD_STATE_TEXT)

  if (NOT DOWNLOAD_STATE_CODE EQUAL 0)
      message(FATAL_ERROR "[Downloading] Failed to download ${DOWNLOAD_OUTPUT}, return value ${DOWNLOAD_STATE}, ${DOWNLOAD_STATE_TEXT}")
  else()
      message(STATUS "[Downloading] Succeed!")
  endif()
endfunction()

if(NOT EXISTS "${DOWNLOAD_OUTPUT}")
  download_file()
else()
  file(SHA256 "${DOWNLOAD_OUTPUT}" FILE_SHA256_DATA)
  if (NOT "${FILE_SHA256_DATA}" STREQUAL "${TS3_SDK_SHA256}")
    file(REMOVE_RECURSE "${DOWNLOAD_OUTPUT}")
    download_file()
  endif()
endif()

if(NOT EXISTS "ts3_sdk_${TS3_SDK_VERSION}")
  file(ARCHIVE_EXTRACT INPUT "${DOWNLOAD_OUTPUT}" DESTINATION "${CURRENT_DIR}")
endif()

set(CMAKE_PREFIX_PATH "${CURRENT_DIR}/ts3_sdk_${TS3_SDK_VERSION}/cmake")
find_package(TSClientSdk REQUIRED)
