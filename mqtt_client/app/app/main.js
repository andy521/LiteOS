require.config({
    baseUrl: './app/js/',
    paths: {
        'assets': '../../assets/',
        'views': '../views',
        'config': 'config/global',
        'angular-resource': '../../assets/lib/angularjs/1.6.4/angular-resource',
        'angular-route': '../../assets/lib/angularjs/1.6.4/angular-route',
        'angular-ui': '../../assets/lib/angular-ui/ui-bootstrap-tpls-2.5.0',
        'ngSlimScroll': '../../assets/lib/angularjs/slimscroll/angular-slimScroll'
    },
    shim: {},
    urlArgs: 'r=' + Math.random()
});
//Init main
require([
    'app', 
    'config', 
    'angular-resource',
    'angular-route',
	'angular-ui',
    'ngSlimScroll',
    'directive/dire-index',
    'route/router',
    'service/brandService',
    'controller/indexCtrl',
    'controller/dashboardCtrl',
    'controller/rackCtrl',
    'controller/compressorCtrl',
    'controller/rackCtrl'], function (app) {
    app.init();
});