/**
 * @file
 * Implements JS behaviours of Modules Checklist module.
 */

(function ($) {
  Drupal.behaviors.modulesChecklist = {
    attach: function() {
      $('#modules-checklist-settings-form input#edit-check-all-enabled').click(function() {
        $checkBoxes = $('#modules-checklist-settings-form input.enabled_module');
        $checkBoxes.attr('checked', !$checkBoxes.attr('checked'));
      })
    }
  }
})(jQuery);
