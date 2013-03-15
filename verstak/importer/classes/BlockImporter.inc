<?php
class BlockImporter{
    private $storage;

    public function __construct(BlockStorage $storage) {
      $this->storage = $storage;
    }
    
    public function Import(){
      module_load_include('inc', 'block', 'block.admin');

      $this->storage->Load();

      $blocks = $this->storage->Get();

      if (count($blocks) == 0) return;

      //$blocks = $this->PrepareFormat($blocks);

      $deltas = $this->BlocksCreate($blocks);
      
      foreach ($deltas as $key => $value){
        $blocks[$key]['delta'] = $value; 
      }

      $this->BlocksConfigure($blocks);
    }

    public function PrepareFormat($blocks) {
        
      foreach ($blocks as $key => $value) {
        if(isset($value['format'])){
          $blocks[$key]['format'] = InputFormatImporter::getFidByName($value['format']);
        }
      }
        
      return $blocks;        
    }

    public function BlocksCreate($blocks) {
      $deltas = array();
      foreach ($blocks as $key => $block){
        if(empty($block['verstak']['create']) || $block['verstak']['create'] === false) continue;
        
        echo "----Creating block----{$block[info]}\n";
        
        $form_state = array();
        $form_state['values'] = $block;
        
        $delta = db_insert('block_custom')
          ->fields(array(
            'body' => $form_state['values']['body']['value'],
            'info' => $form_state['values']['info'],
            'format' => $form_state['values']['body']['format'],
          ))
          ->execute();
        
        $block['delta'] = $delta;
        $deltas[$key] = $block['delta'];
      }
      return $deltas;
    }
    
    public function BlocksConfigure($blocks) {
      foreach($blocks as $block){
        echo "----Configure block----{$block[info]}\n";
        
        //Add block to regions of different themes
        foreach ($block['regions'] as $theme => $region) {
          echo "----Region----{$block[info]}\n";
          $block_fields = array();
          $block_fields['delta']  = $block['delta'];
          $block_fields['module'] = $block['module'];
          $block_fields['delta']  = $block['delta'];
          $block_fields['weight'] = $block['weight'];
          $block_fields['status'] = $block['status'];
          $block_fields['visibility'] = $block['visibility'];
          $block_fields['theme']  =  $theme;
          $block_fields['region'] = $region;
          $block_fields['pages'] = $block['pages'];
          $res = drupal_write_record('block', $block_fields);
          echo 'Result';
          var_dump($res);
        }
        
        $form = array();
        $form_state['values'] = $block;
        $form_state['values']['form_id'] = 'block_admin_configure';
        echo 'Set css class\n';
        block_class_form_submit($form, &$form_state);
      }
    }
    
    
    public function BlocksOutline($blocks) {
      
      foreach ($blocks as $block){
        $form_state['values'] = $block;
        
        db_update('block')
          ->fields(array(
            'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
            'pages' => trim($form_state['values']['pages']),
            'status' => (int)($region != BLOCK_REGION_NONE),
          ))
          ->condition('theme', 'zen')
          ->execute();
      }
      drupal_set_message(t('The block settings have been updated.'));
    }

}
