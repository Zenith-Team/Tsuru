#pragma once

#include "nn/olv/report.h"

// Download
#include "nn/olv/download/downloadcommunitydatalistparam.h"
#include "nn/olv/download/downloadedcommunitydata.h"
#include "nn/olv/download/downloadeddatabase.h"
#include "nn/olv/download/downloadedtopicdata.h"
#include "nn/olv/download/downloadpostdatalistparam.h"

// Upload
#include "nn/olv/upload/uploadparambase.h"
#include "nn/olv/upload/uploadpostdatabypostappparam.h"
#include "nn/olv/upload/uploadpostdataparam.h"

namespace nn { namespace olv {

class DownloadedPostData;

class InitializeParam {
public:
    InitializeParam();

    Result SetWork(u8* work, const u32 workSize);
};

Result DownloadCommunityDataList(DownloadedCommunityData* communityDataList, u32* communityDataListSize, const u32 communityDataListMaxSize, const DownloadCommunityDataListParam* downloadParam);
Result DownloadPostDataList(DownloadedTopicData* topicData, DownloadedPostData* postDataList, u32* downloadedPostDataNum, const u32 downloadPostDataMaxNum, const DownloadPostDataListParam* downloadParam);

Result UploadPostDataByPostApp(const UploadPostDataByPostAppParam* param = nullptr);

u32 GetErrorCode(const Result& out);

Result Initialize(const InitializeParam* param);

} }
