'use strict';
define(['app','config'],function(app,config){
    app.config(['$locationProvider','$routeProvider', function($locationProvider,$routeProvider) {
  $locationProvider.hashPrefix('!');
  $routeProvider.otherwise({redirectTo: '/'});
    }]);

    app.config(['$locationProvider','$routeProvider', function($locationProvider,$routeProvider) {
      $routeProvider.when('/dashboard', {
        templateUrl: 'app/views/dashboard.html',
        controller: 'dashboardCtrl'
      })
      .when('/rack', {
        templateUrl: 'app/views/rack.html',
        controller: 'rackCtrl'
      })
      .when('/compressor', {
        templateUrl: 'app/views/compressor.html',
        controller: 'compressorCtrl'
	  })
      .when('/storeProfile', {
        templateUrl: 'app/views/storeProfile.html',
        controller: 'storeProfileCtrl'
      })
      .when('/suctionGroup', {
        templateUrl: 'app/views/suctionGroup.html',
        controller: 'suctionGroupCtrl'
      })
      .when('/condensor', {
        templateUrl: 'app/views/condensor.html',
        controller: 'condensorCtrl'
      })
      .when('/case', {
        templateUrl: 'app/views/case.html',
        controller: 'caseCtrl'
      });
}]);
});
// angular.module('app',['ngRoute','app.dashboard'])




// angular.module('app.dashboard',['ngRoute'])

// .config(['$locationProvider','$routeProvider', function($locationProvider,$routeProvider) {
//   $routeProvider.when('/dashboard', {
//     templateUrl: 'app/views/dashboard.html',
//     controller: 'dashboardCtrl'
//   });
// }]);

// angular.module('app')
// .config(["$stateProvider","$urlRouterProvider",
// function($stateProvider,$urlRouterProvider){

// $urlRouterProvider
//     .otherwise('app.dashboard');
//     $stateProvider
//     .state('app',{
//         abstract:true,
//         url:'/app',
//         templateUrl:'app/views/app.html'
//     })
//     .state('app.dashboard',{
//         views:{
//             "@app":{
//                 templateUrl:'app/views/dashboard.html',
//                 controller:'dashboardCtrl'
//             }
//         }
//     })
// }]);