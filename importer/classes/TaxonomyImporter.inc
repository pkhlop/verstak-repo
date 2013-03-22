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

      static $vocabs = array();
      $vocabs = $vocabs ?: taxonomy_get_vocabularies(NULL);

      foreach ($vocabs as $vocab_object) {
        if ($vocab_object->machine_name == $vocab['machine_name']) {
          drush_log(t('Dictionary "!name" already existed.', array('!name' => $vocab['machine_name'])), 'warning');
          return ;
        }
      }

      taxonomy_vocabulary_save((object)$vocab);
      drush_log(t('Dictionary "!name" has been created.', array('!name' => $vocab['machine_name'])), 'ok');
    }

    public function VocabConfigure($vocab) {
        
    }

    public function VocabItems($vocab) {
        $items = array_filter(explode("\n", $vocab['items']));

        $vocab['vid'] = $this->getVidByName($vocab['name']);
        
        foreach($items as $weight => $name){
          $this->addTaxonomyTerm($name, $vocab, '', $weight);
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
    
    protected function addTaxonomyTerm($name, $vocab, $description = '', $weight = 0) {

      $term = taxonomy_get_term_by_name($name, $vocab['machine_name']);
      if(!empty($term)) {
        drush_log(t('Term "!name [vid:!vid tid:!tid]" already existed.', array('!name' => $name,
            '!vid' => $vocab['vid'],
            '!tid' => current($term)->tid)),
          'warning');
        return ;
      }

      $form_values = array();
      $form_values['name'] = $name;
      $form_values['description'] = $description;
      $form_values['vid'] = $vocab['vid'];
      $form_values['weight'] = $weight;


      taxonomy_term_save((object)$form_values);

      drush_log(t('Term "!name [vid:!vid tid:!tid]" has been created.', array('!name' => $name, '!vid' => $vocab['vid'],
          '!tid' => $form_values['tid'])),
        'ok');

      return $form_values['tid'];
    }
}
