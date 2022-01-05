[@deriving sexp]
// This type is mutually recursive with DHExp, has
// to be defined in the DHExp module
type t = DHExp.environment;
include VarMap;

let id_env = (ctx: VarCtx.t): t =>
  VarMap.map(
    xt => {
      let (x, _) = xt;
      DHExp.BoundVar(x);
    },
    ctx,
  );
