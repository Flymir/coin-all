// ******************** FlopCpp **********************************************
// File: MP_boolean.cpp
// $Id$
// Author: Tim Helge Hultberg (thh@mat.ua.pt)
// Copyright (C) 2003 Tim Helge Hultberg
// All Rights Reserved.
//****************************************************************************

#include "MP_boolean.hpp"
#include "MP_constant.hpp"
#include "MP_domain.hpp"
#include "MP_set.hpp"

using namespace std;

namespace flopc {

    class Boolean_bool : public Boolean_base {
	friend class MP_boolean;
    private:
	Boolean_bool(bool b) : B(b) {}
	bool evaluate() const {
	    return B; 
	}
	bool B;
    };

    class Boolean_Constant : public Boolean_base {
	friend class MP_boolean;
    private:
	Boolean_Constant(const Constant& c) : C(c) {}
	bool evaluate() const {
	    return C->evaluate(); 
	}
	Constant C;
    };

    class Boolean_SUBSETREF : public Boolean_base {
	friend class MP_boolean;
    private:
	Boolean_SUBSETREF(SUBSETREF& c) : C(&c) {}
	bool evaluate() const {
	    if (C->evaluate() == outOfBound) {
		return false;
	    } else {
		return true;
	    }
	}
	SUBSETREF* C;
    };

    class Boolean_negate : public Boolean_base {
	friend MP_boolean operator!(const MP_boolean& b);
    private:
	Boolean_negate(const MP_boolean& b) : B(b) {}
	bool evaluate() const {
	    return !(B->evaluate());
	}
	MP_boolean B;
    };

    class Boolean_and : public Boolean_base {
	friend MP_boolean operator&&(const MP_boolean& e1, const MP_boolean& e2);
    private:
	Boolean_and(const MP_boolean& e1, const MP_boolean e2) : left(e1), right(e2) {}
	bool evaluate() const {
	    return left->evaluate() && right->evaluate();
	}
	MP_boolean left, right;
    };

    class Boolean_or : public Boolean_base {
	friend MP_boolean operator||(const MP_boolean& e1, const MP_boolean& e2);
    private:
	Boolean_or(const MP_boolean& e1, const MP_boolean& e2) : left(e1), right(e2) {}
	bool evaluate() const {
	    return left->evaluate() || right->evaluate();
	}
	MP_boolean left, right;
    };

    class Boolean_alltrue : public Boolean_base {
	friend MP_boolean alltrue(const MP_domain& d, const MP_boolean& b);
    private:
	Boolean_alltrue(const MP_domain& d, const MP_boolean& b) : D(d), B(b) {}
	bool evaluate() const {
	    return true;
	}
	MP_domain D;
	MP_boolean B;
    };

    class Comparison : public Boolean_base {
    protected:
	Comparison(const Constant& e1, const Constant& e2) : left(e1), right(e2) {}
	Constant left,right;
    };

    class Boolean_lessEq : public Comparison {
	friend MP_boolean operator<=(const MP_index_exp& e1, const MP_index_exp& e2);
	friend MP_boolean operator<=(const Constant& e1, const Constant& e2);
    private:
	Boolean_lessEq(const Constant& e1, const Constant& e2) : Comparison(e1,e2) {}
	bool evaluate() const;
    };

    class Boolean_less : public Comparison {
	friend MP_boolean operator<(const MP_index_exp& e1, 
				    const MP_index_exp& e2);
	friend MP_boolean operator<(const Constant& e1, const Constant& e2); 
    private:
	Boolean_less(const Constant& e1, const Constant& e2) : Comparison(e1,e2) {}
	bool evaluate() const; 
    };

    class Boolean_greaterEq : public Comparison {
	friend MP_boolean operator>=(MP_index& e1, MP_index& e2);
	friend MP_boolean operator>=(const MP_index_exp& e1, 
				     const MP_index_exp& e2);
	friend MP_boolean operator>=(const Constant& e1, const Constant& e2);
    private:
	Boolean_greaterEq(const Constant& e1, const Constant& e2) : 
	    Comparison(e1,e2) {}
	bool evaluate() const;
    };

    class Boolean_greater : public Comparison {
	friend MP_boolean operator>(const MP_index_exp& e1, const MP_index_exp& e2);
	friend MP_boolean operator>(const Constant& e1, const Constant& e2);
    private:
	Boolean_greater(const Constant& e1, const Constant& e2): Comparison(e1,e2) {}
	bool evaluate() const;
    };

    class Boolean_equal : public Comparison {
	friend MP_boolean operator==(const MP_index_exp& e1, const MP_index_exp& e2);
	friend MP_boolean operator==(const Constant& e1, const Constant& e2);
    private:
	Boolean_equal(const Constant& e1, const Constant& e2) : Comparison(e1,e2) {}
	bool evaluate() const;
    };

    class Boolean_not_equal : public Comparison {
	friend MP_boolean operator!=(const MP_index_exp& e1, const MP_index_exp& e2);
	friend MP_boolean operator!=(const Constant& e1, const Constant& e2);
    private:
	Boolean_not_equal(const Constant& e1, const Constant& e2) : Comparison(e1,e2) {}
	bool evaluate() const;
    };


    MP_boolean alltrue(const MP_domain& d, const MP_boolean& b) {
	return new Boolean_alltrue(d,b);
    }

    MP_boolean operator!(const MP_boolean& b) {
	return new Boolean_negate(b);
    }
    MP_boolean operator&&(const MP_boolean& e1, const MP_boolean& e2) {
	return new Boolean_and(e1, e2);
    }
    MP_boolean operator||(const MP_boolean& e1, const MP_boolean& e2) {
	return new Boolean_or(e1, e2);
    }
    MP_boolean operator<=(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_lessEq(e1, e2);
    } 
    MP_boolean operator<=(const Constant& e1, const Constant& e2) {
	return new Boolean_lessEq(e1, e2);
    }
    MP_boolean operator<(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_less(e1, e2);
    }
    MP_boolean operator<(const Constant& e1, const Constant& e2) {
	return new Boolean_less(e1, e2);
    }
    MP_boolean operator>=(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_greaterEq(e1, e2);
    }
    MP_boolean operator>=(const Constant& e1, const Constant& e2) {
	return new Boolean_greaterEq(e1, e2);
    }
    MP_boolean operator>(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_greater(e1, e2);
    }
    MP_boolean operator>(const Constant& e1, const Constant& e2) {
	return new Boolean_greater(e1, e2);
    }
    MP_boolean operator==(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_equal(e1, e2);
    }
    MP_boolean operator!=(const MP_index_exp& e1, const MP_index_exp& e2) {
	return new Boolean_not_equal(e1, e2);
    }
    MP_boolean operator==(const Constant& e1, const Constant& e2) {
	return new Boolean_equal(e1, e2);
    }
    MP_boolean operator!=(const Constant& e1, const Constant& e2) {
	return new Boolean_not_equal(e1, e2);
    }

} // End of namespace flopc

using namespace flopc;

MP_boolean::MP_boolean(bool b) : Handle<Boolean_base*>(new Boolean_bool(b)) {} 

MP_boolean::MP_boolean(const Constant& c) : 
    Handle<Boolean_base*>(new Boolean_Constant(c)) {}

MP_boolean::MP_boolean(SUBSETREF& c) : 
    Handle<Boolean_base*>(new Boolean_SUBSETREF(c)) {}

bool  Boolean_lessEq::evaluate() const {
    return (left->evaluate() <= right->evaluate());
}
bool  Boolean_less::evaluate() const {
    return (left->evaluate() < right->evaluate());
}
bool Boolean_greaterEq::evaluate() const {
    return (left->evaluate() >= right->evaluate());
}
bool Boolean_greater::evaluate() const {
    return (left->evaluate() > right->evaluate());
}
bool Boolean_equal::evaluate() const {
    return (left->evaluate() == right->evaluate());
} 
bool Boolean_not_equal::evaluate() const {
    return (left->evaluate() != right->evaluate());
} 


