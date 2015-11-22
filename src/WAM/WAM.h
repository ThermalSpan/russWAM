


class WAM {

protected:
    // Put instructions
    void put_variable (RegType t, int regId, argRegId);
    void put_value (RegType t, int regId, int argRegId);
    void put_unsafe_value (int regId, int argRegId);
    void put_structure (int functorId, int argRegId);
    void put_list (int argRegId);
    void put_constant (int functorId, int argRegId);

    // Get instructions
    void get_variable (RegType t, int regId, argRegId);
    void get_value (RegType t, int regId, int argRegId);
    void get_structure (int functorId, int argRegId);
    void get_list (int argRegId);
    void get_constant (int functorId, int argRegId);

    // Set instructions
    void set_variable (RegType t, int regId);
    void set_value (RegType t, int regId);
    void set_local_balue (RegType t, int regId);
    void set_constant (int functorId);
    void set_void (int n);

    // Unify Intructions 
    void unify_variable (RegType t, int regId);
    void unify_value (RegType t, int regId);
    void unify_local_value (RegType t, int regId);
    void unify_constant (int functorId);
    void unify_void (int n);
};
