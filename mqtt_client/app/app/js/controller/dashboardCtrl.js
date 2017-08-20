define(['app','config'],function(app,config){
    app.controller('dashboardCtrl', ["$scope","$compile", function ($scope,$compile) {
        $scope.t="test";
    }]);
});