// welcomePage dummy for running in browser
//var welcomePage = {
//voxAccountStatus: function () {
//    return 'logged-in';
//    return 'not-logged-in';
//    return 'premium';
//},
//isOldUser: function () {
//    return true;
//    return false;
//},
//isMas: function () {
//    return true;
//    return false;
//},
//nextSlideOpened_: function() {}
//};

(function ($) {
 
 var wp = welcomePage;
// voxAccountUserDidUpdateStatus();

  /*Initializing Welcome Page slides order*/
  if(!wp.isOldUser()) {
    shiftToSlide('.item-p-1');
  }

  /*Subscribing Handlers*/
  $('.next-btn').on('click', function(){
    moveToNextSlide.call(this);
    wp.nextSlideOpened_(true);
  });

  $('.close-btn').on('click', function(e){
    e.preventDefault();
//        setupVoxFileTypesSupport();
    wp.closeAndStartUsing();
  });
  $('#facebook-signup-btn').on('click', function(e){
    e.preventDefault();
    wp.voxAccountSignupWithFacebook();
//    moveToNextSlide.call(this);
//    wp.nextSlideOpened_(false);
  });
  $('#google-signup-btn').on('click', function(e){
    e.preventDefault();
    wp.voxAccountSignupWithGoogle();
//    moveToNextSlide.call(this);
//    wp.nextSlideOpened_(false);
  });
  $('#email-signup-btn').on('click', function(e){
    e.preventDefault();
    wp.voxAccountSignupWithEmail();
//    moveToNextSlide.call(this);
//    wp.nextSlideOpened_(false);
  });
  $('#signin-btn').on('click', function(e){
    e.preventDefault();
    wp.voxAccountSignin();
//    moveToNextSlide.call(this);
//    wp.nextSlideOpened_(false);
  });

  $('#month-plan-btn').on('click', function (e) {
    e.preventDefault();
    wp.voxAccountBuyMonthSubscription();
  });

  $('#year-plan-btn').on('click', function (e) {
    e.preventDefault();
    wp.voxAccountBuyYearSubscription();
  });

  $('#buynow-btn').on('click', function (e) {
    e.preventDefault();
    wp.voxAccountOpenPurchasePage();
  });

  /**Showing first Slide*/
  $('#slides').addClass('visible');

})(jQuery);

function moveToNextSlide() {
  /** Skipping next slide if its hidden */
  $('#back-ground').addClass('visible');
  $(this).parents('section')
    .css({'-webkit-transform': 'translateX(-100%)'})
    .nextAll('section:not(.hidden)')
    .first()
    .css({'-webkit-transform': 'translateX(0)'})
    .find('.animated').css({
    '-webkit-animation-play-state': 'running',
    'animation-play-state': 'running'
  });
}

function shiftToSlide(selector) {
  $('.item-p').addClass('no-transition');
  $(selector)
    .css({'-webkit-transform': 'translateX(0)'})
    .prevAll()
    .css({'-webkit-transform': 'translateX(-100%)'});
  setTimeout(function () {
    $(selector)
      .removeClass('no-transition')
      .nextAll()
      .removeClass('no-transition');
  }, 600);
}

function updatePrices(monthPlanPrice, yearPlanPrice, hasTrial) {
  $('#month-plan-btn').text(monthPlanPrice + ' / month');
  $('#year-plan-btn').text(yearPlanPrice + ' / year');
  
//  if (hasTrial) {
//    $('#free-trial-info').show();
//  } else {
//    $('#free-trial-info').hide();
//  }
}

function voxAccountUserDidUpdateStatus() {
    var status = welcomePage.voxAccountStatus();
    switch (status) {
        case 'logged-in':
            
            $('.item-p-4').addClass('hidden'); /** Remove Sign Up page */
            if(!welcomePage.isMas()) {
                $('.item-p-5-1, .item-p-5-2').addClass('hidden'); /** set final slide to "Registered not premium user." */
            }
            break;
        case 'premium':
            
            $('.item-p-4').addClass('hidden');
            $('.item-p-5-1').addClass('hidden'); /** set final slide to "Registered premium user." */
            break;
        case 'not-logged-in':
            /** Uncomment if You need DMG user to see Buy Now slide after skipping signup*/
            // if(!user.isMas) {
            //   $('.item-p-4 .skip').removeClass('close-btn').addClass('next-btn');
            //   $('.item-p-5-1, .item-p-5-2').addClass('hidden'); /* set final slide to "Registered not premium user." */
            // }
        default:
            break;
    }
    
}
 
function voxAccountUserDidLoggedIn() {
  var status = welcomePage.voxAccountStatus();
  switch (status) {
    case 'logged-in':
      /** Directing MAS user to "MAS purchase" slide, DMG user to "Registered not premium slide" */
      welcomePage.isMas() ? shiftToSlide('.item-p-5-1') : shiftToSlide('.item-p-5-3');
      break;
    case 'premium':
      shiftToSlide('.item-p-5-2');
      break;
    case 'not-logged-in':
      /** Doing nothing in this case*/
    default:
      break;
  }
}

function startPurchaseProgress() {
    $('.loading-progress').addClass('visible');
}

function stopPurchaseProgress() {
    $('.loading-progress').removeClass('visible');
}


