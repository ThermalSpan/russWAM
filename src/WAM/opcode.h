enum OpCode {
    OC_cut_variable,
    OC_put_variable,
    OC_put_value,
    OC_put_unsafevalue,
    OC_put_structure,
    OC_put_list,
    OC_put_constant,
    OC_set_variable,
    OC_set_value,
    OC_set_localvalue,
    OC_set_constant,
    OC_set_void,
    OC_allocate,
    OC_deallocate,
    OC_call,
    OC_execute,
    OC_proceed,
    OC_switch_on_term,
    OC_switch_on_constant,
    OC_switch_on_structure,
    OC_get_variable,
    OC_get_value,
    OC_get_structure,
    OC_get_list,
    OC_get_constant,
    OC_unify_variable,
    OC_unify_value,
    OC_unify_localvalue,
    OC_unify_constant,
    OC_unify_void,
    OC_try_me_else,
    OC_retry_me_else,
    OC_trust_me,
    OC_try,
    OC_retry,
    OC_trust,
    OC_neck_cut,
    OC_get_level,
    OC_cut,
    OC_printHeap,
    OC_printArgRegisters,
    OC_printResultArg,
    OC_printHeapCell,
    OC_unifyHeapCells,
    OC_write,
    OC_terminate
};

