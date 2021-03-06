<?php
/**
 * @file
 * imagex_contest.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function imagex_contest_default_rules_configuration() {
  $items = array();
  $items['rules_imagex_contest_close_entries'] = entity_import('rules_config', '{ "rules_imagex_contest_close_entries" : {
      "LABEL" : "ImageX Contest Close Entries",
      "PLUGIN" : "rule set",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_published" : { "node" : [ "node" ] } },
              { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_contest_entry_deadline" } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_contest_entry_open" } },
              { "NOT data_is_empty" : { "data" : [ "node:field-contest-entry-open" ] } }
            ],
            "DO" : [
              { "data_set" : { "data" : [ "node:field-contest-entry-open" ], "value" : 0 } },
              { "mail" : {
                  "to" : "[node:author:mail]",
                  "subject" : "Entry submissions for the contest \\u0022[node:title]\\u0022 are now closed",
                  "message" : "Hi,\\r\\n\\r\\nThis is an automated email to say entry submissions for the contest \\u0022[node:title]\\u0022 are now closed and you now need to select your finalist(s).\\r\\n\\r\\nContest name: [node:title]\\r\\nContest URL: [node:url]\\r\\n\\r\\nSend from: [site:name] ([site:url])",
                  "from" : "[site:mail]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Close Entries To Contest"
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_close_voting'] = entity_import('rules_config', '{ "rules_imagex_contest_close_voting" : {
      "LABEL" : "ImageX Contest Close Voting",
      "PLUGIN" : "rule set",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_published" : { "node" : [ "node" ] } },
              { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_contest_voting_deadline" } },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_contest_voting_open" } },
              { "NOT data_is_empty" : { "data" : [ "node:field-contest-voting-open" ] } }
            ],
            "DO" : [
              { "data_set" : { "data" : [ "node:field-contest-voting-open" ], "value" : 0 } },
              { "mail" : {
                  "to" : "[node:author:mail]",
                  "subject" : "Voting on the contest \\u0022[node:title]\\u0022 is now closed",
                  "message" : "Hi,\\r\\n\\r\\nThis is an automated email to say voting on the contest \\u0022[node:title]\\u0022 is now closed and you now need to select your winner(s).\\r\\n\\r\\nContest name: [node:title]\\r\\nContest URL: [node:url]\\r\\n\\r\\nSend from: [site:name] ([site:url])",
                  "from" : "[site:mail]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Close Voting On Contest"
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_entry_as_finalist'] = entity_import('rules_config', '{ "rules_imagex_contest_entry_as_finalist" : {
      "LABEL" : "ImageX Contest Entry As Finalist",
      "PLUGIN" : "rule set",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : {
        "entry_node" : { "label" : "Entry Node", "type" : "node" },
        "notify_entry_author" : { "label" : "Notify Entry Author", "type" : "integer" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "contest_entity" : "Contest entity" } },
            "IF" : [
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_status" } },
              { "NOT data_is" : {
                  "data" : [ "entry-node:field-contest-entry-status" ],
                  "value" : { "value" : { "1" : "1" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_contest" } },
              { "data_is" : { "data" : [ "notify-entry-author" ], "value" : "1" } }
            ],
            "DO" : [
              { "entity_fetch" : {
                  "USING" : {
                    "type" : "node",
                    "id" : [ "entry-node:field-contest-entry-contest:nid" ]
                  },
                  "PROVIDE" : { "entity_fetched" : { "contest_entity" : "Contest entity" } }
                }
              },
              { "mail" : {
                  "to" : "[entry-node:author:mail]",
                  "subject" : "Congratulations, your contest entry was selected as a finalist.",
                  "message" : "Congratulations, your contest entry on the contest, [contest-entity:title] ([contest-entity:url]) was selected as a finalist.\\r\\n\\r\\nYour entry: [entry-node:title] ([entry-node:url])\\r\\n\\r\\n",
                  "from" : "[contest-entity:author:mail]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Email Finalist"
          }
        },
        { "RULE" : {
            "IF" : [
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_status" } },
              { "NOT data_is" : {
                  "data" : [ "entry-node:field-contest-entry-status" ],
                  "value" : { "value" : { "1" : "1" } }
                }
              }
            ],
            "DO" : [
              { "data_set" : {
                  "data" : [ "entry-node:field-contest-entry-status" ],
                  "value" : { "value" : { "1" : "1" } }
                }
              }
            ],
            "LABEL" : "Entry As Finalist"
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_entry_as_winner'] = entity_import('rules_config', '{ "rules_imagex_contest_entry_as_winner" : {
      "LABEL" : "ImageX Contest Entry As Winner",
      "PLUGIN" : "rule set",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : {
        "entry_node" : { "label" : "Entry Node", "type" : "node" },
        "notify_entry_author" : { "label" : "Notify Entry Author", "type" : "integer" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "contest_entity" : "Contest entity" } },
            "IF" : [
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_status" } },
              { "NOT data_is" : {
                  "data" : [ "entry-node:field-contest-entry-status" ],
                  "value" : { "value" : { "2" : "2" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_contest" } },
              { "data_is" : { "data" : [ "notify-entry-author" ], "value" : "1" } }
            ],
            "DO" : [
              { "entity_fetch" : {
                  "USING" : {
                    "type" : "node",
                    "id" : [ "entry-node:field-contest-entry-contest:nid" ]
                  },
                  "PROVIDE" : { "entity_fetched" : { "contest_entity" : "Contest entity" } }
                }
              },
              { "mail" : {
                  "to" : "[entry-node:author:mail]",
                  "subject" : "Congratulations, your contest entry was selected as a winner.",
                  "message" : "Congratulations, your contest entry on the contest, [contest-entity:title] ([contest-entity:url]) was selected as a winner.\\r\\n\\r\\nYour entry: [entry-node:title] ([entry-node:url])\\r\\n",
                  "from" : "[contest-entity:author:mail]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Email Winner"
          }
        },
        { "RULE" : {
            "IF" : [
              { "entity_has_field" : { "entity" : [ "entry-node" ], "field" : "field_contest_entry_status" } },
              { "NOT data_is" : { "data" : [ "entry-node:field-contest-entry-status:1" ], "value" : "2" } }
            ],
            "DO" : [
              { "data_set" : {
                  "data" : [ "entry-node:field-contest-entry-status" ],
                  "value" : { "value" : { "1" : "1", "2" : "2" } }
                }
              }
            ],
            "LABEL" : "Entry As Winner"
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_entry_deadline'] = entity_import('rules_config', '{ "rules_imagex_contest_entry_deadline" : {
      "LABEL" : "ImageX Contest Entry Deadline",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : [ "node_insert", "node_update" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-contest-entry-deadline" ] } },
        { "NOT data_is_empty" : { "data" : [ "node:field-contest-entry-open" ] } }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_imagex_contest_close_entries",
            "date" : [ "node:field-contest-entry-deadline" ],
            "identifier" : "close_contest_entries_[node:nid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_entry_deadline_remove_schedule'] = entity_import('rules_config', '{ "rules_imagex_contest_entry_deadline_remove_schedule" : {
      "LABEL" : "ImageX Contest Entry Deadline Remove Schedule",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
        { "data_is_empty" : { "data" : [ "node:field-contest-entry-open" ] } }
      ],
      "DO" : [
        { "schedule_delete" : {
            "component" : "rules_imagex_contest_close_entries",
            "task" : "close_contest_entries_[node:nid]"
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_voting_deadline'] = entity_import('rules_config', '{ "rules_imagex_contest_voting_deadline" : {
      "LABEL" : "ImageX Contest Voting Deadline",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : [ "node_insert", "node_update" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-contest-voting-deadline" ] } },
        { "NOT data_is_empty" : { "data" : [ "node:field-contest-voting-open" ] } }
      ],
      "DO" : [
        { "schedule" : {
            "component" : "rules_imagex_contest_close_voting",
            "date" : [ "node:field-contest-voting-deadline" ],
            "identifier" : "close_contest_voting_[node:nid]",
            "param_node" : [ "node" ]
          }
        }
      ]
    }
  }');
  $items['rules_imagex_contest_voting_deadline_remove_schedule'] = entity_import('rules_config', '{ "rules_imagex_contest_voting_deadline_remove_schedule" : {
      "LABEL" : "ImageX Contest Voting Deadline Remove Schedule",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "imagex_contest" ],
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : [ "node_insert", "node_update", "node_delete" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "contest" : "contest" } } } },
        { "data_is_empty" : { "data" : [ "node:field-contest-voting-open" ] } }
      ],
      "DO" : [
        { "schedule_delete" : {
            "component" : "rules_imagex_contest_close_voting",
            "task" : "close_contest_voting_[node:nid]"
          }
        }
      ]
    }
  }');

  features_alter_code('rules_config', $items);

  return $items;
}
