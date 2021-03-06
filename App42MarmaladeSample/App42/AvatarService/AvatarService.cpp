//
//  AvatarService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Shephertz Technologies Pvt Ltd on 02/07/14.
//
//

#include "AvatarService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "Connector.h"
#include "App42API.h"
#include "App42Constants.h"
#include "App42AvatarResponse.h"



// define the static..
AvatarService* AvatarService::_instance = NULL;

AvatarService::AvatarService()
{
    
}

AvatarService* AvatarService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new AvatarService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

AvatarService* AvatarService::getInstance()
{
	return _instance;
}

void AvatarService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}


string AvatarService::buildCreateAvatarFromFacebookRequest(const char* userName, const char* avatarName, const char* accessToken, const char* webUrl, const char* description)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *avatarJSON = cJSON_CreateObject();
    
    // first construct the user
    if (strlen(userName))
    {
        cJSON_AddStringToObject(avatarJSON, "userName", userName);
    }
    
    if (strlen(avatarName))
    {
        cJSON_AddStringToObject(avatarJSON, "avatarName", avatarName);
    }
    
    if (strlen(accessToken))
    {
        cJSON_AddStringToObject(avatarJSON, "accessToken", accessToken);
    }
    
    if (strlen(webUrl))
    {
        cJSON_AddStringToObject(avatarJSON, "webUrl", webUrl);
    }
    
    if (strlen(description))
    {
        cJSON_AddStringToObject(avatarJSON, "description", description);
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "avatar", avatarJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(avatarJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
}


void AvatarService::CreateAvatarFromFacebook(const char* avatarName, const char* userName, const char* accessToken, const char* description, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(avatarName, "Avatar Name");
        Util::throwExceptionIfStringNullOrBlank(accessToken, "Access Token");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestBody = buildCreateAvatarFromFacebookRequest(userName, avatarName, accessToken,"", description);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "avatar";
    resource.append("/facebook");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42AvatarResponse::onComplete));
}

void AvatarService::CreateAvatarFromWebURL(const char* avatarName, const char* userName, const char* webUrl, const char* description, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(avatarName, "Avatar Name");
        Util::throwExceptionIfStringNullOrBlank(webUrl, "WebURL");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestBody = buildCreateAvatarFromFacebookRequest(userName, avatarName, "",webUrl, description);
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "avatar";
    resource.append("/weburl");
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePost(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42AvatarResponse::onComplete));
}

void AvatarService::GetAvatarByName(const char* avatarName, const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(avatarName, "Avatar Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["userName"] = userName;
    signParams["avatarName"] = avatarName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "avatar";
    resource.append("/");
    resource.append(userName);
    resource.append("/");
    resource.append(avatarName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, response, app42response_selector(App42AvatarResponse::onComplete));
}

void AvatarService::GetAllAvatars(const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "avatar";
    resource.append("/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, response, app42response_selector(App42AvatarResponse::onComplete));
}

void AvatarService::GetCurrentAvatar(const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    signParams["userName"] = userName;
    string signature = Util::signMap(secretKey, signParams);
    
    /**
     * Creating URL
     */
    string resource = "avatar";
    resource.append("/current/");
    resource.append(userName);
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(encodedUrl, headers, response, app42response_selector(App42AvatarResponse::onComplete));
}

void AvatarService::ChangeCurrentAvatar(const char* avatarName, const char* userName, App42CallBack* pTarget,SEL_App42CallFuncND pSelector)
{
    App42AvatarResponse *response = new App42AvatarResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfStringNullOrBlank(avatarName, "Avatar Name");
        
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signParams;
    populateSignParams(signParams);
    string requestBody = buildCreateAvatarFromFacebookRequest(userName, avatarName, "","", "");
    signParams["body"] = requestBody;
    string signature = Util::signMap(secretKey, signParams);
    
    Util::printMap(signParams);
    /**
     * Creating URL
     */
    string resource = "avatar";
    string baseUrl = getBaseUrl(resource);
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    Util::app42Trace("\n BaseUrl = %s",baseUrl.c_str());
    Util::app42Trace("\n RequestBody = %s",requestBody.c_str());
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(encodedUrl, headers, requestBody.c_str(), response, app42response_selector(App42AvatarResponse::onComplete));
}

