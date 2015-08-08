//
//  TestStorageService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestStorageService.h"
#include <fstream>

#define GO_HOME 103

TestStorageService::TestStorageService()
{
    storageService = App42API::BuildStorageService();
    dbName = "Your_DB_Name"; //Replace this with the DB_NAME you created from AppHQ Console
    collectionName = "Your_Collection_Name";
}

TestStorageService::~TestStorageService()
{
    StorageService::Terminate();
}

string getJsonString(string key1, string value1,string key2,string value2)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON_AddStringToObject(bodyJSON, key1.c_str(), value1.c_str());
    cJSON_AddStringToObject(bodyJSON, key2.c_str(), value2.c_str());
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    cJSON_Delete(bodyJSON);
	free(cptrFormatted);
    
	return bodyString;
}

void TestStorageService::insertJsonDocument()
{
    
    const char* jsonDoc ="{\"name\":\"Nick\",\"age\":30,\"phone\":\"xxx-xxx-xxx\"}";
    //App42API::setLoggedInUser("Shephertz");
    //storageService->setAdminKey(APP_ADMIN_KEY);
    
    storageService->InsertJsonDocument(dbName, collectionName, jsonDoc,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::insertJsonDocumentWithApp42Object()
{
    
    StorageService *storageService = App42API::BuildStorageService();
    App42Object *object = new App42Object();
    object->setObject("name", "Nick");
    object->setObject("age", 30);
    
    storageService->InsertJsonDocument(dbName, collectionName, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));

    
    delete object;
    object = nullptr;
}

void TestStorageService::findAllCollections()
{
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllCollections(dbName, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}


void TestStorageService::findAllDocuments()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["orderByAscending"] = "Score";
    storageService->setOtherMetaHeaders(otherMetaHeaders);
    storageService->FindAllDocuments(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findAllDocumentsByPaging()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    int max = 2;
    int offset = 0;
    storageService->FindAllDocuments(dbName, collectionName,max,offset,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findAllDocumentsCount()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllDocumentsCount(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocumentById()
{
    StorageService *storageService = App42API::BuildStorageService();
    //const char* docId = "";
    storageService->FindDocumentById(dbName, collectionName, docId, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}


void TestStorageService::findDocumentByQuery()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //const char* key1 = "name";
    //const char* value1 = "Nick";
    const char* key = "UserId";
    string value1 = "100004971962878";
    string value2 = "John";

    std::vector<string> userIds;
    userIds.push_back(value1);
    userIds.push_back(value2);
    cJSON *jsonArr = cJSON_CreateArray();
    cJSON *jsonObj = cJSON_CreateString(value1.c_str());
    cJSON_AddItemToArray(jsonArr, jsonObj);

    //Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key, userIds, APP42_OP_INLIST);
    //Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);
    
    /*map<string,string>otherMetaHeaders;
    otherMetaHeaders["orderByDescending"] = "createdAt";
    storageService->setOtherMetaHeaders(otherMetaHeaders);*/
    
    storageService->FindDocumentsByQuery(dbName, collectionName,query2,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocumentByQueryWithPaging()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);
    int max =2;
    int offset = 0;
    storageService->FindDocumentsByQueryWithPaging(dbName, collectionName,query3,max,offset,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}
void TestStorageService::findDocumentByQueryWithPagingOrderBy()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key1 = "name";
    const char* value1 = "Nick";
    
    const char* orderByKey = "_$createdAt";
    
    Query *query = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    int max =2;
    int offset = 0;

    storageService->FindDocsWithQueryPagingOrderBy(dbName, collectionName,query,max,offset,orderByKey,APP42_ORDER_DESCENDING,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocumentsByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key="name";
    const char* value = "Rajeev Ranjan";
    storageService->FindDocumentByKeyValue(dbName, collectionName,key,value,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocsByKeyValueByOrder()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["orderByAscending"] = "createdAt";
    const char* key="name";
    const char* value = "Nick";
    storageService->FindDocumentByKeyValue(dbName, collectionName,key,value,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::deleteDocumentById()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* docId = "538c4fafe4b0b33395a73eef";
    storageService->DeleteDocumentsById(dbName, collectionName,docId,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::deleteDocumentByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "role";
    const char* value = "Developer";
    storageService->DeleteDocumentsByKeyValue(dbName, collectionName,key,value,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::deleteAllDocuments()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->DeleteAllDocuments(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::addOrUpdateKeys()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev Ranjan", "age", "31");
    const char* docId = "docId";
    const char* jsonDoc = "{\"name\":\"Nick\",\"age\":30,\"phone\":\"xxx-xxx-xxx\"}";
    storageService->AddOrUpdateKeys(dbName, collectionName, docId, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::addOrUpdateKeysWithApp42Object()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    const char* docId = "docId";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    storageService->AddOrUpdateKeys(dbName, collectionName, docId, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::updateDocByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //const char* jsonDoc = getJsonString("name", "Rajeev", "age", "41");

    const char* key = "name";
    const char* value = "Nick";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    
    storageService->UpdateDocumentByKeyValue(dbName, collectionName, key, value, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::updateApp42DocByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "name";
    const char* value = "Nick";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->UpdateDocumentByKeyValue(dbName, collectionName, key, value, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
    
    delete object;
    object = nullptr;
}



void TestStorageService::updateDocByDocID()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev Ranjan", "age", "31");
    const char* docId = "533e5c89e4b0ae7acf86b1f0";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    storageService->UpdateDocumentByDocId(dbName, collectionName, docId, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::updateApp42DocByDocId()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* docId = "docId";
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->UpdateDocumentByDocId(dbName, collectionName, docId, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
    
    delete object;
    object = nullptr;
}

void TestStorageService::saveOrUpdateDocumentByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev", "age", "41");
    
    const char* key = "name";
    const char* value = "Nick";
    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    storageService->SaveOrUpdateDocumentByKeyValue(dbName, collectionName, key, value, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::saveOrUpdateApp42DocumentByKeyValue()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    const char* key = "name";
    const char* value = "Nick";
    
    App42Object *object = new App42Object();
    object->setObject("name", "John");
    object->setObject("age", "20");
    
    storageService->SaveOrUpdateDocumentByKeyValue(dbName, collectionName, key, value, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
    
    delete object;
    object = nullptr;
}


void TestStorageService::updateDocumentByQuery()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    //string jsonDoc = getJsonString("name", "Rajeev", "age", "41");
    
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);

    const char* jsonDoc = "{\"Company\":\"Shephertz Technologies\"}";
    
    storageService->UpdateDocumentByQuery(dbName, collectionName, query3, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::updateDocumentWithApp42ObjectByQuery()
{
    //App42API::setIsTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    const char* key1 = "name";
    const char* value1 = "Nick";
    const char* key2 = "age";
    const char* value2 = "30";
    
    Query *query1 = QueryBuilder::BuildQuery(key1, value1, APP42_OP_EQUALS);
    Query *query2 = QueryBuilder::BuildQuery(key2, value2, APP42_OP_GREATER_THAN_EQUALTO);
    Query *query3 = QueryBuilder::CompoundOperator(query1, APP42_OP_OR, query2);


    
    App42Object *object = new App42Object();
    object->setObject("name", "Rajeev");
    object->setObject("age", "30");
    
    storageService->UpdateDocumentByQuery(dbName, collectionName, query3, object, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
    
    delete object;
    object = nullptr;
}



/***
 * Callbacks
 */

void TestStorageService::onStorageRequestCompleted(App42CallBack *sender, void *response)
{
    App42StorageResponse *storageResponse = (App42StorageResponse*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
    
    if (storageResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",storageResponse->getTotalRecords());
        for(std::vector<App42Storage>::iterator it = storageResponse->storages.begin(); it != storageResponse->storages.end(); ++it)
        {
            printf("\n DbName=%s",it->dbName.c_str());
            printf("\n CollectionName=%s",it->collectionName.c_str());
            printf("\n RecordCount=%lf\n",it->recordCount);
            
            for(std::vector<JSONDocument>::iterator iit = it->jsonDocArray.begin(); iit != it->jsonDocArray.end(); ++iit)
            {
                docId = iit->getDocId().c_str();
                
                printf("\n DocId=%s",iit->getDocId().c_str());
                
                printf("\n Event=%s",iit->getEvent().c_str());
                printf("\n Owner=%s",iit->getOwner().c_str());
                printf("\n UpdatedAt=%s",iit->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",iit->getJsonDoc().c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",storageResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",storageResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",storageResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",storageResponse->httpErrorCode);
    }
}

