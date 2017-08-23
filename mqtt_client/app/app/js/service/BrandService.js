/**
 * Created by gary on 2017--5-30
 * 
 */
define(['app', 'config'], function(app, config) {
    app.service('brandService', ['$http', function($http) {
        // console.info(config.webapi);
        this.getBrands = function() {
            var myService = {
                async: function() {
                    var req = {
                        method: 'GET',
                        url: 'https://192.168.0.11/iot/temperature',
                        withCredentials: true,
                        headers: {
                            'Content-Type': 'application/json; charset=utf-8',
                        },
                        data: {}
                    }
                    var promise = $http(req);
                    // Return the promise to the controller
                    return promise;
                }
            };
            return myService;

        };
        this.getBrands2 = function() {
            var myService = {
                async: function() {
                    var req = {
                        method: 'GET',
                        url: config.webapi + '/brandapi/list',
                        withCredentials: false,
                        headers: {
                            'Content-Type': 'application/json; charset=utf-8',
                        },
                        data: {}
                    }
                    var promise = $http(req);
                    // Return the promise to the controller
                    return promise;
                }
            };
            return myService;

        };
    }]);
});