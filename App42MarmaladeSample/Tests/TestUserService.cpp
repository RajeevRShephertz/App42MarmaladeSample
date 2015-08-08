//
//  TestUserService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestUserService.h"

TestUserService::TestUserService()
{
    userService = App42API::BuildUserService();
}

TestUserService::~TestUserService()
{
    printf("\nTestUserService   Deleted\n");
    UserService::Terminate();
}

void TestUserService::createUser()
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "ShephertzTech";
    const char* pwd = "*******";
    const char* emailId = "shephertzTech@shephertz.co.in";
    userService->CreateUser(userName, pwd, emailId,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::createUserWithCustomData()
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "App42Cocos2dx";
    const char* pwd = "*******";
    const char* emailId = "App42Cocos2dx@shephertz.co.in";
    
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    
    App42Object *object = new App42Object();
    object->setObject("FirstName", "App42");
    object->setObject("LastName", "CloudAPI");
    App42API::setDbName(dbName);
    userService->AddUserInfo(object, collectionName);
    userService->CreateUser(userName, pwd, emailId,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUserWithCustomData()
{
    UserService *userService = App42API::BuildUserService();
    const char* key = "FirstName";
    const char* value = "App42";
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    //App42API::setDbName(dbName);
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    userService->setQuery(dbName, collectionName, query);
    //userService->setQuery(collectionName, query);
    const char* userName = "App42Cocos2dx";
    userService->GetUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getAllUsersWithCustomData()
{
    UserService *userService = App42API::BuildUserService();
    const char* key = "FirstName";
    const char* value = "App42";
    const char* dbName = "jsonDocument2";
    const char* collectionName = "TestingScore";
    App42API::setDbName(dbName);
    Query *query = QueryBuilder::BuildQuery(key, value, APP42_OP_EQUALS);
    userService->setQuery(collectionName, query);
    userService->GetAllUsers(this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}



void TestUserService::createUserWithRoles()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nick";
    const char* pwd = "*******";
    const char* emailId = "nick@shephertz.co.in";
    
    vector<string>roles;
    roles.push_back("s_admin");
    roles.push_back("s_manager");
    roles.push_back("s_techlead");

    userService->CreateUser(userName, pwd, emailId, roles, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::assignRoles()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "RajeevRanjan111";
    
    vector<string>roles;
    roles.push_back("s_Manager");
    roles.push_back("COO");

    
    userService->AssignRoles(userName, roles, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::authenticateUser()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nick243";
    const char* pwd = "*******";
   // const char* emailId = "nick@shephertz.co.in";
    
    userService->Authenticate(userName, pwd, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::authenticateUserViaEmail()
{
    UserService *userService = App42API::BuildUserService();
    
    const char* pwd = "*******";
    const char* emailId = "nick@shephertz.com";
    
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["emailAuth"] = "true";
    userService->setOtherMetaHeaders(otherMetaHeaders);
    
    userService->Authenticate(emailId, pwd, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUserWithUserName()
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->GetUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}



void TestUserService::getUserWithEmailId()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* emailId = "nicky@shephertz.co.in";

    userService->GetUserByEmailId(emailId, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
    
}

void TestUserService::getAllUser()
{
    //App42API::setIsTraceEnabled(true)(false);
    //UserService *userService = App42API::BuildUserService();
    std::map<string,string> otherMetaHeaders1;
    otherMetaHeaders1["orderByDescending"] = "name";
    userService->setOtherMetaHeaders(otherMetaHeaders1);
    userService->GetAllUsers(this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getAllUsersByPaging()
{
    ////App42API::setIsTraceEnabled(true);
    //UserService *userService = App42API::BuildUserService();
    int max = 10;
    int offset = 0;
    
    std::map<string,string> otherMetaHeaders2;
    userService->setOtherMetaHeaders(otherMetaHeaders2);
    userService->GetAllUsers(max,offset,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::getAllUsersCount()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetAllUsersCount(this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::lockUser()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->LockUser(userName,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::unlockUser()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    userService->UnlockUser(userName,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getLockedUsers()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetLockedUsers(this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getLockedUsersByPaging()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    int max = 1;
    int offset = 0;
    userService->GetLockedUsers(max,offset,this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::getLockedUsersCount()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    userService->GetLockedUsersCount(this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::updateEmail()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nick";
    const char* emailId = "nick@shephertz.com";
    //userService->setAdminKey(APP_ADMIN_KEY);
    userService->UpdateEmail(userName,emailId, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::deleteUser()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan11";
    userService->DeleteUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::deleteUserPermanent()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nick";
    map<string,string>otherMetaHeaders;
    otherMetaHeaders["deletePermanent"] = "true";
    userService->setOtherMetaHeaders(otherMetaHeaders);
    
    userService->DeleteUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::changePassword()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    const char* userName = "Nicky";
    const char* oldPwd = "*******";
    const char* newPwd = "8800927154";
    userService->ChangeUserPassword(userName, newPwd, oldPwd, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::resetPassword()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    const char* userName = "Brown";
    user->ResetUserPassword(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::createOrUpdateProfile()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    App42User user;
    user.userName = "Nicky";
    App42UserProfile userProfile;
    userProfile.firstName = "Nick";
    userProfile.lastName = "Gill";
    userProfile.setSex(App42UserProfile::MALE);
    userProfile.dateOfBirth = "";
    userProfile.city = "Houston";
    userProfile.state = "Texas";
    userProfile.pincode = "74193";
    userProfile.country = "USA";
    userProfile.mobile = "+1-1111-111-111";
    userProfile.homeLandLine = "+1-2222-222-222";
    userProfile.officeLandLine = "+1-33333-333-333";
    user.profile = userProfile;
    userService->createOrUpdateProfile(&user, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUserByProfileData()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();

    App42UserProfile userProfile;
    userProfile.firstName = "Nick";
    userProfile.lastName = "Gill";
//    userProfile.setSex(App42UserProfile::MALE);
//    userProfile.dateOfBirth = "";
//    userProfile.city = "Houston";
//    userProfile.state = "Texas";
//    userProfile.pincode = "74193";
//    userProfile.country = "USA";
//    userProfile.mobile = "+1-1111-111-111";
//    userProfile.homeLandLine = "+1-2222-222-222";
//    userProfile.officeLandLine = "+1-33333-333-333";
//    printf("Sex=%s",userProfile.getSex().c_str());
    userService->GetUsersByProfileData(&userProfile, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::logout()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* sessionId = "78724aea-3c8d-43a0-98d9-84df215ba510";
    userService->Logout(sessionId, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getRolesByUser()
{
    ////App42API::setIsTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    const char* userName = "Nicky";
    userService->GetRolesByUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUsersByRole()
{
    UserService *userService = App42API::BuildUserService();
    const char* role = "COO";
    userService->GetUsersByRole(role, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));

}
void TestUserService::revokeRole()
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan111";
    const char* role = "COO";
    userService->RevokeRole(userName, role, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}
void TestUserService::revokeAllRoles()
{
    UserService *userService = App42API::BuildUserService();
    const char* userName = "RajeevRanjan111";
    userService->RevokeAllRoles(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUsersByGroup()
{
    UserService *userService = App42API::BuildUserService();

    vector<string>users;
    users.push_back("RajeevRanjan111");
    users.push_back("Nicky");
    userService->GetUsersByGroup(users, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}
void TestUserService::createUserWithProfile()
{
    const char* userName = "Brown";
    const char* password = "chocobrowny";
    const char* email = "brown@shephertz.co.in";
    App42UserProfile userProfile;
    userProfile.firstName = "Brown";
    userProfile.city = "NewYork";
    userProfile.mobile = "1234567890";
    
    UserService *userService = App42API::BuildUserService();
    userService->CreateUserWithProfile(userName, password, email, &userProfile, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
    
}


/**
 * Callback Methods
 */
void TestUserService::onUserRequestCompleted(App42CallBack *sender, void *response)
{
    App42UserResponse *userResponse = (App42UserResponse*)response;
    printf("\ncode=%d...=%d",userResponse->getCode(),userResponse->isSuccess);
    printf("\nResponse Body=%s",userResponse->getBody().c_str());
    
    if (userResponse->isSuccess)
    {
        printf("\nTotalRecords=%d",userResponse->getTotalRecords());
        
        for(std::vector<App42User>::iterator it = userResponse->users.begin(); it != userResponse->users.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Email=%s",it->email.c_str());
            printf("\n SessionId=%s",it->sessionId.c_str());
            printf("\n isAccountLocked=%d",it->isAccountLocked);
            printf("\n CreatedOn=%s",it->createdOn.c_str());
            printf("\n Password=%s",it->password.c_str());
            //Fetching Profile Info
            printf("\n FirstName=%s",it->profile.firstName.c_str());
            printf("\n LastName=%s",it->profile.lastName.c_str());
            printf("\n Sex=%s",it->profile.getSex().c_str());
            printf("\n Date of Birth=%s",it->profile.dateOfBirth.c_str());
            printf("\n Line1=%s",it->profile.line1.c_str());
            printf("\n Line2=%s",it->profile.line2.c_str());
            printf("\n City=%s",it->profile.city.c_str());
            printf("\n State=%s",it->profile.state.c_str());
            printf("\n Pincode=%s",it->profile.pincode.c_str());
            printf("\n Country=%s",it->profile.country.c_str());
            printf("\n Mobile=%s",it->profile.mobile.c_str());
            printf("\n HomeLandLine=%s",it->profile.homeLandLine.c_str());
            printf("\n OfficeLandLine=%s",it->profile.officeLandLine.c_str());

            //Fetching Roles
            std::vector<string>::iterator iit;
            for(iit=it->roleList.begin(); iit!=it->roleList.end(); ++iit)
            {
                printf("\n%s",iit->c_str());
            }
            
            //Fetching Custom Data
            std::vector<JSONDocument>::iterator jsonDoc;
            for(jsonDoc=it->jsonDocArray.begin(); jsonDoc!=it->jsonDocArray.end(); ++jsonDoc)
            {
                printf("\n CreatedAt=%s",jsonDoc->getCreatedAt().c_str());
                printf("\n DocId=%s",jsonDoc->getDocId().c_str());
                printf("\n Event=%s",jsonDoc->getEvent().c_str());
                printf("\n Owner=%s",jsonDoc->getOwner().c_str());
                printf("\n UpdatedAt=%s",jsonDoc->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",jsonDoc->getJsonDoc().c_str());
            }
        }
    }
    else
    {
        printf("\nerrordetails:%s",userResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",userResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",userResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",userResponse->httpErrorCode);
    }
    
}

