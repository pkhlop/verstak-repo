<?php
class MenuImporter{
  private $storage;

  public function __construct(MenuStorage $storage) {
    $this->storage = $storage;
  }

  public function Import(){
    $this->storage->Load();
    $menus = $this->storage->Get();

    module_load_include('inc', 'menu', 'menu.admin');

    foreach ($menus as $menu){
      $form_state = array();
      $form_state['values'] = $menu['menu'];
      echo "Add menu: \"{$menu[menu][menu_name]}::{$menu[menu][title]}\"\n";
      drupal_form_submit('menu_edit_menu', $form_state);

      $items = $this->ParseMenuItems($menu);
      $this->ImportMenuItems($menu, $items);
    }
    drupal_flush_all_caches();
    menu_rebuild();
  }

  function getIndent($string){
    $i = 0;
    while(($string[$i]==" " || $string[$i]=="\t") && $i<count($string)){$i++;}
    return $i;
  }

  private function addSubItem(&$lines, &$i, $indent){
    if( $i >= count($lines) ) return false;
    $res = array();
    while($i<count($lines) && $this->getIndent($lines[$i]) >= $indent){
      if(!trim($lines[$i])){
        $i++;
        continue;
      }
      if( $this->getIndent($lines[$i]) == $indent ){
        $nible = explode('|', trim($lines[$i]));
        $res[] = array('name'=>$nible[0], 'path'=>$nible[1]);
        $i++;
      }else{
        $res[count($res)-1]['sub'] = $this->addSubItem($lines, $i, $this->getIndent($lines[$i])) ;
      }
    }
    return $res;
  }

  public function ParseMenuItems($menu) {
    $lines = explode("\n", $menu['items']);

    $items = array();
    $indent = 0;
    $items = $this->addSubItem($lines, $i, $indent);

    return $items;
  }

  private function addMenuItems($items, $parent, $menu){
    //include_once(drupal_get_path('module', 'menu') .'/menu.admin.inc');
    
    $i=-50;
    foreach ($items as $item){
      $i++;
      $menu_item = array(
        'link_path'  => $item['path'],
	'link_title' => $item['name'],
	'menu_name'  => "menu-{$menu[menu][menu_name]}",
	'plid'	     => $parent,
      );
      
      echo "Add menu item {$item[name]}|{$item[path]}\n";
      $mlid = menu_link_save($menu_item);
      if(isset($item['sub'])){
        $this->addMenuItems($item['sub'], $mlid, $menu);
      }
    }
  }

  public function ImportMenuItems($menu, $items) {
    var_dump($items);
    $this->addMenuItems($items, 0, $menu);
  }
}