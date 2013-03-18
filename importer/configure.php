<?php
require_once __DIR__.'/conf/import_config.inc';
require_once __DIR__.'/lib/init.inc';

global $user;
$user = user_load(1);

echo "Start Permission Setup ==========================\n";

//Set default theme
variable_set('theme_default', 'zen');
$query = db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'zen'");
$query->execute();

/*//Permissions settings for authenticated user
$auth_user_permissions = array(
  
);
permissions_grant_permissions('authenticated user', $auth_user_permissions);
 * 
 */

// Vkuchaem developerskii rejim v module less
// variable_set("less_devel", 1);

// Instal theme for admin
// $user=user_load(1);
// user_save($user, array('theme'=>'rootcandy_dark'), $category = 'account');

//Выключаем кеш блоков
variable_set("block_cache", 0); 


/************Lightbox2 custom configuration********************
variable_set('lightbox2_border_size', 1);
variable_set('lightbox2_overlay_opacity', 0.0);
variable_set('lightbox2_disable_zoom', TRUE);
variable_set('lightbox2_use_alt_layout', TRUE);
*/

//Taxonomy menu settings
variable_set('taxonomy_menu_path_3', "taxonomy_menu_path_default");
variable_set('taxonomy_menu_vocab_menu_3', "menu-categories");
variable_set('taxonomy_menu_vocab_parent_3', "0");
variable_set('taxonomy_menu_voc_item_3', 0);

//Set permissions for anonymouse
function _add_permissions($rid, $permissions) {
  if (!is_array($permissions)) { 
    $permissions = explode(', ', $permissions);
  }
  $query = explode(', ', db_result(db_query("SELECT perm FROM {permission} WHERE rid=%d", $rid)));
  $current_perms = $query->execute();
  foreach($permissions as $permission) {
    if (!in_array($permission, $current_perms)) {
        $current_perms[] = $permission;
      }
    }
  $current_perms = implode(', ', $current_perms);  
  $return = db_query("UPDATE {permission} SET perm= '%s' WHERE rid=%d", $current_perms, $rid);
  return $return;
}

//$new_perms = array();
//$rid = 1;
//$new_perms[] = 'use custom search';
//$new_perms[] = 'use custom search blocks';
//$new_perms[] = 'search content';
//$new_perms[] = 'use advanced search';
//$add_permission_status = _add_permissions($rid, $new_perms);
//$rid = 2;
//$add_permission_status_aun = _add_permissions($rid, $new_perms);

//Flush all caches
drupal_flush_all_caches();