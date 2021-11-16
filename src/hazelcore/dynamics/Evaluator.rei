/**  Invalid Input codes:
     0 = out of fuel
     1 = free or invalid variable
     2 = ap invalid boxed function val
     3 = boxed value not a int literal 2
     4 = boxed value not a int literal 1
     5 = bad pattern match
     6 = Cast BV Hole Ground
     7 = boxed value not a float literal 1
     8 = boxed value not a float literal 2
     9 = boxed value not a string literal 1
    10 = boxed value not a string literal 2
    11 = boxed value not a subscript string literal 1
    12 = boxed value not a subscript int literal 1
    13 = boxed value not a subscript int literal 2
 */

[@deriving sexp]
type ground_cases =
  | Hole
  | Ground
  | NotGroundOrHole(HTyp.t) /* the argument is the corresponding ground type */;

let evaluate: DHExp.t => EvaluatorResult.t;

/* closed substitution [d1/x]d2*/
let subst_var: (DHExp.t, Var.t, DHExp.t) => DHExp.t;

let subst: (Environment.t, DHExp.t) => DHExp.t;
