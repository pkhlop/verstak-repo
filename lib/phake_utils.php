<?php

  function do_exec($command)
  {

    $output = array();
    $return_value = -1;
    exec($command, $output, $return_value);

    return $return_value;
  }

  function try_command($command, $message = null, $on_success = null, $on_error = null)
  {

    if ($message === null) {
      $message = "Command: \n $command";
    }

    if ($on_success === null) {
      $on_success = "finished";
    }

    if ($on_error === null) {
      $on_error = "ERROR: \n $command";
    }

    builder_info($message);

    if (is_bool($command) && $command === false) {
      builder_error($on_error);
      is_builder_error($message, true);
    }

    if (!is_bool($command) && is_int($command) && $command !== 0) {
      builder_error($on_error);
      is_builder_error($message, true);
    }

    if (!is_bool($command) && !is_int($command) && do_exec($command)) {
      builder_error($on_error);
      is_builder_error($message, true);
    }

    if (!is_builder_error($message)) {
      builder_message($on_success);
    }

  }

  function builder_info($message, $flags = array())
  {
    writeln(green($message));
  }

  function builder_message($message, $flags = array())
  {
    writeln(yellow($message));
  }

  function is_builder_error($scope = null, $flag = null)
  {
    static $data = array();

    //set error
    if ($scope !== null && $flag !== null) {
      $data[$scope] = $flag;
      return $flag;
    }

    //get ststus for scope
    if ($scope !== null) {
      return isset($data[$scope]) ? $data[$scope] : false;
    }

    //globals status. try to find at least one error flag
    foreach ($data as $flag) {
      if ($flag) return $flag;
    }

    //no error found
    return false;

  }

  function builder_error($message, $flags = array())
  {
    writeln(red($message));

    //TODO: Add config setting "stop on fail" "don't stop on fail"
//  die();
  }
