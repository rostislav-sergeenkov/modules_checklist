/**
 * @file
 * Implements JS behaviours of Modules Checklist module.
 */

(function ($) {
  Drupal.behaviors.modulesChecklist = {
    attach: function() {
      /**
       * Implements 'Check all enabled modules' logic.
       */
      $('#modules-checklist-settings-form input#edit-check-all-enabled').click(function(event) {
        var checkedEnabledModules = $('#modules-checklist-settings-form input:checked.enabled_module');
        var allEnabledModules = $('#modules-checklist-settings-form input.enabled_module');
        var allDisabledModules = $('#modules-checklist-settings-form input.disabled_module');

        if (checkedEnabledModules.length != allEnabledModules.length) {
          allEnabledModules.attr('checked', 'checked');
          allDisabledModules.removeAttr('checked');
        }
        else {
          checkedEnabledModules.removeAttr('checked');
        }
      });
    }
  }
})(jQuery);
