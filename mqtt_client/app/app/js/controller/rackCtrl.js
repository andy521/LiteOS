define(['app','config'],function(app,config){
    app.controller('rackCtrl', ["$scope","$compile", function ($scope,$compile) {
        $scope.t="test";
    }]);
});