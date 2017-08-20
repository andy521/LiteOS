define(['app', 'config'], function (app, config) {
     
    app.controller('indexCtrl', ['$scope', '$compile', 'brandService', function ($scope, $compile, brandService) {
        //get data from api service
        brandService.getBrands().async().then(function (data) {
            $scope.brands = data.data;
            console.info($scope.brands);
            $("#divTxt").text($scope.brands.length);
        }, function (msg) {
            //Show the messages
            console.info(msg.data.ErrorCode + ":" + msg.data.Message);
            return msg;
        });

       
    }]);
});