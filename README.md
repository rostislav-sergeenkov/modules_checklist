# Introduction

Modules Checklist provides and maintains control over enabled modules
on the project.

Initially it was written for a long-term Drupal project to control and monitor
hundreds of enabled modules on multiple environments
(DEV, QA, Stage, Load Test, Prod etc) during development.

 * For a full description of the module, visit the project page:
 [http://drupal.org/project/modules-checklist]
 (http://drupal.org/project/modules_checklist)

 * To submit bug reports and feature suggestions, or to track changes:
 [https://drupal.org/project/issues/modules-checklist]
 (https://drupal.org/project/issues/modules_checklist)

## Modules Checklist.

Modules Checklist compares enabled modules with defined in settings.php
lists of required and optional modules and warns site administrator 
(on the Status report page and by email) in case of any discrepancy.

It also warns if user is trying to disable required module or enable 
the module which should be disabled.

 - Required module must be enabled at any time. Critical for the Project.
 List of required modules must be added to settings.php 
 as $conf['modules_checklist_required_modules'] containing array 
 of machine_names of the required modules.
 - Optional or ignored module can be enabled, disabled or absent.
 List of optional modules must be added to settings.php 
 as $conf['modules_checklist_optional_modules'] containing array 
 of machine_names of the optional modules.
 Example: Devel, Coder, Views UI
 (modules for developers and site administrators).
 - Disabled modules. Not required and not optional modules should be disabled
 or removed from the Project if this is possible. If you aren't sure 
 about the module just add it to the list of optional modules.

Configuration: /admin/config/development/modules_checklist_settings
See "How to set up the module" section of the configuration page 
for the detailed step by step instructions.
Use "Configuration helper" to generate $conf variables.

## Modules Checklist log.

Records in database who and when installed / enabled / disabled / unistalled
modules on the site.

Provides administration UI (/admin/reports/modules_checklist_log)
for browsing log and filtering log entries.

# Installation and unistallation

Install and uninstall as you would normally install / unistall
a contributed Drupal module.
See [http://drupal.org/documentation/install/modules-themes/modules-7]
(http://drupal.org/documentation/install/modules-themes/modules-7)
for further information.

# Configuration

 1. Make sure you are able to modify /sites/default/settings.php
 for your Project.
 2. Go to the module settings page -
 /admin/config/development/modules_checklist_settings
 3. Check modules you wish to track using "Configuration" form.
 Modules can be required, optional or disabled.
 4. Click "Generate config" button to generate code for $conf variables.
 5. Copy the generated code and paste it into sites/default/settings.php
 to complete setup.

In case of any discrepancy with the list of required or disabled modules
error message will be shown on the module settings page and Status report page.

If "Modules Checklist log" is enabled then you will be able to browse
(/admin/reports/modules_checklist_log) the history and figure out
who installed / enabled / disabled / unistalled the module.

# Future releases

 - fix issue: module folder can be renamed, however it doesn't show up 
 in status check. 
 - define constants for messages like 'Please enable it or exclude...'.
 - highlight rows in the log table according to the priority of modules
 (required, optional etc).
 - highlight rows in Configuration helper if required module is disabled (red) 
 or disabled module is enabled (orange).
 - create views field handlers for Module Names and Type (Status) instead of
 altering for Views fields in modules_checklist_log_views_pre_render() and in
 modules_checklist_log_views_data_alter().
 - add filters by Date - use Date popup.
 - get list of email tokens dynamically instead of using 
 modules_checklist_get_email_tokens().

# Maintainers

 * Rostislav Sergeenkov [https://www.drupal.org/u/rostislav-sergeenkov]
 (https://www.drupal.org/u/rostislav-sergeenkov)

This project has been sponsored by EPAM Systems
[https://www.drupal.org/epam-systems] (https://www.drupal.org/epam-systems)

# Test cases

(Information about test cases can be helpful to QA team testing the module)

## Module Checklist

### 1. Test Status message

 * on Status report page (/admin/reports/status)
 * on the Module Checklist configuration page 
 (admin/config/development/modules_checklist_settings)
 
   - Check if $conf variables (required and optional lists of modules) exist 
   in settings.php.   
   - Check if any required modules have been removed from the file system.
   - Check if any required modules are disabled.
   - Checks if any module is enabled which doesn't belong 
   - the list of required or optional modules.

 * on Modules page (/admin/modules)
   - Shows up on enable, disable, unistall the required and disabled modules.
 
### 2. Test error / warning message 

 * On Modules page form submit
   - if required disabled module has been enabled.
   - if required enabled module has been disabled.   
 * On Modules page (unistall phase) form submit
   - if required module is going to be unistalled.
   - if required module has been unistalled.

### 3. Test "Modules Checklist settings" page 

 (/admin/config/development/modules_checklist_settings)   
 
 * access to the page must be restricted with the permission 
 'configure modules_checklist settings'.
 * Check "How to set up the module" if this section is clear 
 for site administrator.  
 * Check "Configuration helper" if it reflects $conf variables in settings.php. 
 Test on absent $conf variables.
 * Check "Set all enabled modules as" radio buttons.
 * Check "Uncheck/exclude all disabled modules".
 * Check form submit logic of "Generate $conf variables" button.
 * Check "Reset" button.
   
### 4. Test email notification (if enabled)

 * Test Validation (/admin/config/development/modules_checklist_settings)
   - if email address / addresses are valid.
   - "Subject" and "Body" fields must be required.  

 * Sends email on install, enable, disable, unistall required module 
 manually using Modules page. Check email content.
 * Sends email on install, enable, disable, unistall required module 
 using Drush page. Check email content.

## Module Checklist log

### 1. Test log UI

 * access to the log must be restricted with the permission 
 'access modules_checklist log'.
 * filters and ordering by click on row titles.
 * log entries that correspond to install, enable, disable, unistall 
 actions on modules.
 
### 2. Check if information available in log 

 (/admin/reports/modules_checklist_log)
 
 * who is disabling the module.
 * who is unistalling the module.
 * remove 'modules_checklist_log_status_*' variables from DB
 * who has previously uninstalled and disabled the module.   
 * who is installing and enabling the module.   
 
### 3. Test "Modules Checklist settings" page 

 (/admin/config/development/modules_checklist_settings) 
 
 * Check log rotation by running cron.
 