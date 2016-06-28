-- ABOUT --



-- MODULES --



-- OPTIONS --



-- REQUIREMENTS, INSTALLATION AND UNINSTALLATION --

Install and uninstall as usual.
See http://drupal.org/documentation/install/modules-themes/modules-7
for further information.

-- CONFIGURATION AND USAGE --


-- INFORMATION --


-- FUTURE RELEASES --

# RELEASE 7x-1.1. Focus on code quality and usability.
 - create include 'all enabled modules' checkbox.
 - highlight rows in the table according to the priority of modules
 (required, optional etc).
 - create views field handlers for Module Names and Type (Status) instead of
 altering for Views fields in modules_checklist_log_views_pre_render().
 - output "Available modules" widget as a table,
 add "Check all enabled modules" checkbox.
 - add email notification if required module on module disabling/un-installation.
 - think about periodic check of systems table to ensure that entry
 for the manually enabled in DB modules is present in the log. If this logic works...
 - add filters by Date - use Date popup.
 After Views regeneration add t() to all titles and labels.
