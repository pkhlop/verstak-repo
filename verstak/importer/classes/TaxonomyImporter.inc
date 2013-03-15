<?php
class TaxonomyImporter{
    private $storage;

    public function __construct(TaxonomyStorage $storage) {
        $this->storage = $storage;
    }

    public function Import(){
        $this->storage->Load();

        $vocabs = $this->storage->Get();
        
        foreach ($vocabs as $vocab){
            $this->VocabCreate($vocab);
            $this->VocabConfigure($vocab);
            $this->VocabItems($vocab);
        }
    }

    public function VocabCreate($vocab) {
        taxonomy_save_vocabulary($vocab);   
    }

    public function VocabConfigure($vocab) {
        
    }

    public function VocabItems($vocab) {
        $items = array_filter(explode("\n", $vocab['items']));
        
        $vid = $this->getVidByName($vocab['name']);
        
        foreach($items as $weight => $name){
            $this->addTaxonomyTerm($name,$vid,'',$weight);
        }
    }
    
    protected function getVidByName($name){
        $vocabs=taxonomy_get_vocabularies();
        foreach($vocabs as $vocab){
            if($vocab->name==$name) {
                return $vocab->vid;
            }
        }
        return false;
    }
    
    protected function addTaxonomyTerm($name, $vid, $description = '', $weight = 0) {

      $form_values = array();
      $form_values['name'] = $name;
      $form_values['description'] = $description;
      $form_values['vid'] = $vid;
      $form_values['weight'] = $weight;
      taxonomy_save_term($form_values);

      return $form_values['tid'];
    }
}
