#include "s3e.h"
#include "IwDebug.h"
#include "TestStorageService.h"
#include "TestUserService.h"

#define API_KEY    "Enter_Your_API_KEY"
#define SECRET_KEY "Enter_Your_SECRET_KEY"

// Main entry point for the application
int main()
{
    //Initialise graphics system(s)
    
    printf("\nHello\n");
    /**
     * Initialise App42API with your API_KEY and SECRET_KEY
     */
    App42API::Initialize(API_KEY, SECRET_KEY);
    App42API::setIsTraceEnabled(true);
    
    /*
     * User Service Test
     */
    TestUserService *testUserService = new TestUserService();
    //testUserService->createUser();
    testUserService->getAllUser();
    
    /*
     * Storage Service Test
     */
    TestStorageService *testStorageService = new TestStorageService();
    testStorageService->insertJsonDocument();
    
    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        
        // Your rendering/app code goes here.


        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    //Terminate modules being used
    delete testStorageService;
    delete testUserService;
    // Return
    return 0;
}
