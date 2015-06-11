#Secure your multiplatform application

With the increasing number of device's shapes, resolutions and features, developing a mobile application has become a real challenge for specialists. The application layout has to be responsive, the application has to meet design guidelines, new APIs and best practices proposed – even sometime imposed – by OS editors.

All these requirements increase the development costs and tend to reduce time spent on a less visible, but equally important feature: the application security. As a result, Gartner foresees that in 2015, 75% of mobile apps will fail basic security test.

AiM Services (http://www.aim-services.ch) and Sysmosoft (http://www.sysmosoft.com) developed in common a Cordova Plugin to help you secure your application
The Sysmosoft SDK first version was available for native iOS and Android applications but not for multi-platform environment.
Thus, thanks to AiM's experience, we decided to develop SenseConnector, a Cordova / Phonegap plugin exposing Sysmosoft SDK‘s features to HTML5 developers on mobile platforms.

Sysmosoft SDK allows two protection levels for the application.

**Offline protection**:

- Screenshots prevention
- Control of data copy/pasting from the application
- Rooted and jail-broken devices detection
- Hacking detection (reverse engineering) for iOS apps

**Online protection**:

- Strong authentication
- User login control based on contextual rules (geofencing)
- Application updates handling
- Creation of a secured channel between the application and the enterprise intranet for all http browser requests (assets, ajax request, REST http services, etc…)
- User inactivity detection
- Timeout session detection

Our plugin (SenseConnector) installation is based on the CLI (command line interface) provided by Cordova project. You can easily add the plugin to an existing Cordova project and automatically benefit from the offline protection. If you want to go further, you can setup the Sense Server in just a few minutes.

SenseConnector Cordova plugin installation for iOS & Android

#Requirements
To perform the operation, the Cordova command-line interface CLI is used. It allows to have a custom project respecting Cordova development standards. The executables are developed using NodeJS and is installed using NPM, the package manager of NodeJS.

The NodeJS and NPM installation package can be found at the following address: http://nodejs.org/

It must be installed on MacOS with the latest version of XCode installed.

For Android, it is necessary to install the Android SDK with API 21 or later and Apache Ant to compile the project. Apache Ant must be in the path of the OS.


#Installation
To create a blank project that will serve as a base for html sources, the procedure is as follows :

- npm –g install cordova
- cordova create ProjectName ch.company.application.id ProjectName
- cd ProjectName
- cordova platform add ios
- cordova platform add android
- Register on the Sysmosoft web site : http://www.sysmosoft.com/sdk/sense-sdk.html

- cordova plugins add https://github.com/devmobileaim/cordovasenseconnector.git

- cordova build ios
- cordova build android
You have a project that you can edit or compile with XCode command line.

 

#Validation
To test the Cordova project please follow the following procedure:

- sudo npm –g install ios-deploy
- sudo npm –g install ios-sim
- cordova run ios
- cordova run android
The application will run in the emulator and double tapping Cmd + Shift + H you can check the overview of the application is well hidden by the Sense SDK. For Android it depends on the version of the os but clicking on the “Exposé” you should see a black thumbnail where the application should be.

 

#Packaging
To build the .ipa you can either use XCode or use the following command line :

- xcrun -sdk iphoneos PackageApplication -v $PWD/platforms/ios/build/device/ProjectName.app -o $PWD/platforms/ios/build/ ProjectName.ipa –embed ../ProjectName.mobileprovision

The development profile has been previously configured on the machine and the .mobileprovision file downloaded from the Apple site.
To build the APK you can use the standard building command of Cordova CLI.
