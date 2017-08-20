define(['app'], function (app) {
    app.directive('refHeader', function () {
        return {
            templateUrl: app.getAppRoot() + "views/main/header.html",
            replace: true,
            restrict:'E',
            link: function (scope, element, attr) {

            }
        }; 
    });
    app.directive('refSidebar', function ($uibModal) {
       
        return {
            templateUrl: app.getAppRoot() + "views/main/sidebar.html",
            replace: true,
            restrict: 'E',
            //controller:myController,
            link: function (scope, element, attr) {
                // console.log($uibModal)
                var sidebars = [1, 2, 3];
                sidebars.forEach(function (a, b) {
                    //点击<-按钮折叠panel
                    $("ul.sidebar" + a + " .foldMenuButton").click(function () {
                        $('.sidebar' + a).width(40);
                        var firstMenuWidth = $('.sidebar1').width();
                        var secondMenuWidth = $('.sidebar2').width();
                        var thirdMenuWidth = $('.sidebar3').width();
                        $('.sidebar2').css("left", firstMenuWidth);
                        $('.sidebar3').css("left", firstMenuWidth + secondMenuWidth);
                        $('.sidebar' + a).addClass("closed");
                        $('.sidebar' + a).removeClass("opened");
                        
                    });
                    //点击title,展开panel
                    $("ul.sidebar" + a + " .title").click(function () {
                        $('.sidebar' + a).width(225);
                        var firstMenuWidth = $('.sidebar1').width();
                        var secondMenuWidth = $('.sidebar2').width();
                        var thirdMenuWidth = $('.sidebar3').width();
                        $('.sidebar2').css("left", firstMenuWidth);
                        $('.sidebar3').css("left", firstMenuWidth + secondMenuWidth);
                        $('.sidebar' + a).removeClass("closed");
                        $('.sidebar' + a).addClass("opened");
                        
                    });
                    //除了 "工具栏" 点击后都应该展开下个sidebar panel.
                    $('.sidebar' + a + ' li[class!="cmdBar"]').click(function () {
                        $('.sidebar' + a + ' li').siblings().removeClass('active');
                        $(this).addClass("active");
                        if (a < 3) {
                            $('.sidebar' + (a + 1)).addClass("showSidebarPanel");
                        }
                        //只要选择了Store,Store detail应该显示
                        if (a == 2) {
                            $("ul.sidebar3 .title").click();
                        }
                    });
                });
                //ul li 没有onchange事件.模拟事件
                var t_chain = 'Food City';
                $('ul[class^="sidebar1"] li[class!="cmdBar"]').click(function () {
                    var curtxt = $(this).children().children().text();
                    if (t_chain != curtxt) {
                        $(".sidebar2 .title").click();
                        $('.sidebar3').removeClass("showSidebarPanel");

                        //加载chain 对应的 stores.
                        loadBrands();
                        
                    }
                    t_chain = curtxt;
                });
                //page-content margin-left设置
                $("ul .title,ul .foldMenuButton,ul li").click(function () {
                    $('.page-content').css("margin-left", $('.sidebar1').width() + $('.sidebar2').width() + $('.sidebar3').width() + "px");
                });
                //scope.addNewChain = function () {
                //    console.info('s');
                //};
                var loadBrands = function () {
                    
                }
                // 点击触发modal
                var ctrl = scope;
                ctrl.items = ['item1', 'item2', 'item3'];
                scope.addNewChain = function () {
                    console.log("addNewChain")
                    $uibModal.open({
                        animation: true,
                        ariaLabelledBy: 'modal-title',
                        ariaDescribedBy: 'modal-body',
                        templateUrl: 'app/views/addNewChain.html',
                        controller: function ($uibModalInstance) {
                            console.log("this is store modal controller");
                            var that = this;
                            this.ok = function (result) {
                                $('.sidebar1').append('<li><a href="javascript:;"><span>' + that.chainName + '</span><span class="arrow "></span></a></li>');
                                $uibModalInstance.close(result);
                            }
                            this.cancel = function (result) {
                                $uibModalInstance.close(result);
                            }
                        },
                        controllerAs: '$ctrl',
                        size: 'sm',
                        resolve: {
                            items: function () {
                                return ctrl.items;
                            }
                        }
                    });
                }
                scope.addNewStore = function () {
                    console.log("addNewStore")
                    $uibModal.open({
                        animation: true,
                        ariaLabelledBy: 'modal-title',
                        ariaDescribedBy: 'modal-body',
                        templateUrl: 'app/views/addNewStore.html',
                        controller: function ($uibModalInstance) {
                            var that = this;
                            console.log("this is store modal controller");
                            this.ok = function (result) {
                                $('.sidebar2').append('<li><a href="javascript:;"><span>' + that.chainName + '</span><span class="arrow "></span></a></li>');
                                $uibModalInstance.close(result);
                            }
                            this.cancel = function (result) {
                                $uibModalInstance.close(result);
                            }
                        },
                        controllerAs: '$ctrl',
                        size: 'sm',
                        resolve: {
                            items: function () {
                                return ctrl.items;
                            }
                        }
                    });
                }
            }
        };
    });
});