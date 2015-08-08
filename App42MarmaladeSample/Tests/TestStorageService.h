//
//  TestStorageService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__

#include <iostream>
#include "App42API.h"

class TestStorageService : public App42CallBack
{
public:
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
   
    TestStorageService();
    ~TestStorageService();
    /**
     * API Test methods
     */
    void insertJsonDocument();
    void insertJsonDocumentWithApp42Object();

    void findAllDocuments();
    void findAllDocumentsByPaging();
    void findAllDocumentsCount();
    void findDocumentById();
    void findDocumentByQuery();
    void findDocumentByQueryWithPaging();
    void findDocumentByQueryWithPagingOrderBy();
    void findDocumentsByKeyValue();
    void deleteDocumentById();
    void deleteDocumentByKeyValue();
    void deleteAllDocuments();
    void addOrUpdateKeys();
    void addOrUpdateKeysWithApp42Object();
    void updateDocByKeyValue();
    void updateApp42DocByKeyValue();
    void updateDocByDocID();
    void updateApp42DocByDocId();
    void saveOrUpdateDocumentByKeyValue();
    void saveOrUpdateApp42DocumentByKeyValue();
    void updateDocumentByQuery();
    void updateDocumentWithApp42ObjectByQuery();
    void findAllCollections();
    void findDocsByKeyValueByOrder();
    void grantAccessOnDoc();
    void revokeAccessOnDoc();
    
    void loadResponseScene();
    /**
     * A selector callback
     */
    void onStorageRequestCompleted(App42CallBack *sender, void *response);
    
private:
    std::string apiKey;
    std::string secretKey;
    const char* dbName;
    const char* collectionName;
    const char* docId;
    int serviceId;
    StorageService *storageService;
};

#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__) */
