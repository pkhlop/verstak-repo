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

        if(isset($block) && isset($block['info'])) {
          db_delete('block_custom')
            ->condition('info', $block['info'])
            ->execute();
        }

        $delta = db_insert('block_custom')
          ->fields(array(
            'body' => $form_state['values']['body']['value'],
            'info' => $form_state['values']['info'],
            'format' => $form_state['values']['body']['format'],
          ))
          ->execute();
        
        $deltas[$key] = $delta;
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
          $block_fields += $region;
          $block_fields['theme']  = $theme;
          $block_fields['module']  = $block['module'];
          $block_fields['delta']  = $block['delta'];


          if(isset($block) && isset($block['module']) && isset($block['delta']) && isset($block_fields['theme'])) {
            db_delete('block')
              ->condition('module', $block['module'])
              ->condition('delta', $block['delta'])
              ->condition('theme', $block_fields['theme'])
            ->execute();
          }

          $res = drupal_write_record('block', $block_fields);

          echo 'Result';
        }
      }
    }
}
