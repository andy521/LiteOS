define(['app','config'],function(app,config){
    app.controller('caseCtrl', ["$scope","$compile", function ($scope,$compile) {
        $scope.t="test";
    }]);
});