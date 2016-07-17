/**
 * @file
 * Implements JS behaviours of Modules Checklist module.
 */

(function ($) {
  Drupal.behaviors.modulesChecklist = {
    attach: function () {
      /**
       * Implements 'Set all enabled modules as' logic.
       */
      $('#modules-checklist-settings-form #edit-check-all input').click(function (event) {
        var checkedValue = $(this).val();

        if (checkedValue == 'required') {
          $('#modules_checklist_table input[data-status="required"][data-enabled="enabled"]').click()
        }
        else if (checkedValue == 'optional') {
          $('#modules_checklist_table input[data-status="optional"][data-enabled="enabled"]').click()
        }
        else if (checkedValue == 'disabled') {
          $('#modules_checklist_table input[data-status="disabled"][data-enabled="enabled"]').click()
        }
      });

      /**
       * Implements 'Uncheck all disabled modules' logic.
       */
      $('#modules-checklist-settings-form input#edit-uncheck-disabled').click(function () {
        if ($(this).attr('checked')) {
          $('#modules_checklist_table input[data-enabled="disabled"]').removeAttr('checked');
          $('#modules_checklist_table input[data-status="disabled"]').removeAttr('checked');
        }
        else {
          $('#modules_checklist_table input[data-checked="1"][data-enabled="disabled"]').attr('checked', 'checked');
        }
      });

      /**
       * Adds behavior similar to native Drupal 'radios' form item.
       */
      $('#modules_checklist_table .form-type-radio input').click(function () {
        var radios = $(this).closest('tr').find('.form-type-radio input');
        var targetId = $(this).attr('id');

        for (var i = 0; i < radios.length; i++) {
          var radioId = $(radios[i]).attr('id');

          if (targetId != radioId) {
            $('#' + radioId).removeAttr('checked');
          }
        }
      })

      /**
       * Checks all modules added to the config.
       */
      $('#modules_checklist_table input[data-checked="1"]').click();
    }

  }
})(jQuery);
