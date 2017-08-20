module.exports = function (grunt) {
    "use strict";
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        uglify: {
            options: {
                banner: '/*! <%= pkg.name %> <%= grunt.template.today("yyyy-mm-dd") %> */\n'
            },
            my_target: {
                files: {
                    'build/all.js': [
                        'assets/lib/jquery/jquery-3.2.1.min.js',
                        'assets/lib/jquery/jquery.cookie.js',
                        'assets/vendors/bootstrap/js/bootstrap.min.js',
                        'assets/lib/requirejs/require.min.js',
                        'assets/lib/angularjs/1.6.4/angular.min.js', 
                        'app/main.js'
                    ],
                    'build/ie.js': [
                        'assets/lib/ie/es5-shim/es5-shim.min.js',
                        'assets/lib/ie/html5shiv/html5shiv.min.js',
                        'assets/lib/ie/json/json3.min.js',
                        'assets/lib/ie/respond/respond.min.js',
                        'assets/lib/ie/ieupdate/ieupdate.js'
                    ]
                }
            }
        },
        cssmin: {
            concat: {
                options: {
                    keepBreaks: true,
                    keepSpecialComments: 0,
                    noAdvanced: false,
                    noRebase: false,
                    root: './',
                    sourceMap: true
                },
                nonull: true,
                src: [
                    'assets/fonts/font-awesome.min.css',
                    'assets/vendors/bootstrap/css/bootstrap.min.css',
                    'app/css/common.css',
                    'app/css/main.css',
                    'app/css/modal.css',
                    'app/css/rack.css'


                    
                ],
                dest: 'build/app.css'
            },
            minify: {
                options: {},
                nonull: true,
                src: [
                    'app/css/default.css',
                    'app/css/style.css'
                    
                ],
                dest: 'build/app.css'
            }
        },
        htmlmin: {
            // dist: {
            //     options: {
            //         collapseWhitespace: true,
            //         collapseBooleanAttributes: true,
            //         removeCommentsFromCDATA: true,
            //         removeOptionalTags: true
            //     },
            //     files: [
            //         {
            //             expand: true,
            //             cwd: 'build',
            //             src: ['*.html', 'app/views/{,*/}*.html'],
            //             dest: 'build'
            //         }
            //     ]
            // },
            dev:{
                file: {
                    'build/header.html':'app/views//header.html',
                    'build/index.html':'app/views//index.html'
                }
                
            }
        },
        jshint: {
            build: ['Gruntfile.js', 'app/js/*.js'],
            options: {
                jshintrc: '.jshintrc'
            }
        },
        connect: {
            server: {
                options: {
                    protocol: 'http',
                    hostname: '0.0.0.0',
                    port: 8081,
                    hostname: '*',
                    base: './',
                    keepalive: true,
                    debug: true,
                    open: true
                }
            }
        },
        // sass: {
        //     dist: {
        //         files: {
        //             'app/css/common.css': 'app/css/common.scss',
        //             'app/css/main.css': 'app/css/main.scss',
        //             'app/css/modal.css': 'app/css/modal.scss',
        //             'app/css/rack.css': 'app/css/rack.scss'
                    
        //         },
        //         options: {
        //             sourcemap: 'inline'
        //         }
        //     }
        // },
        watch: {
            build: {
                files: ['app/**/*.js', 'app/**/*.css', 'app/**/*.html'],
                tasks: [/* 'sass',*/'uglify', 'cssmin:concat'],
                options: { spawn: false }
            }
        }
    });

    grunt.loadNpmTasks('grunt-contrib-uglify');
    grunt.loadNpmTasks('grunt-contrib-jshint');
    grunt.loadNpmTasks('grunt-contrib-cssmin');
    // grunt.loadNpmTasks('grunt-contrib-htmlmin');
    grunt.loadNpmTasks('grunt-contrib-sass');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-contrib-connect');
    grunt.registerTask('watchit',['connect','watch']);
    grunt.registerTask('default', [/*'sass',*/ 'uglify', 'cssmin:concat', 'connect:server']);
};