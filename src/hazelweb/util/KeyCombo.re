module Js = Js_of_ocaml.Js;
module Dom_html = Js_of_ocaml.Dom_html;

module Details = {
  type t = {
    mod_keys: ModKeys.t,
    key: Key.t,
  };

  let mk = (mod_keys, key) => {mod_keys, key};
  let plain = key => {mod_keys: ModKeys.not_held, key};
  let no_ctrl_alt_meta = key => {mod_keys: ModKeys.no_ctrl_alt_meta, key};
  let shift = key => {mod_keys: ModKeys.shift, key};
  let ctrl = key => {mod_keys: ModKeys.ctrl, key};
  let alt = key => {mod_keys: ModKeys.alt, key};
  let meta = key => {mod_keys: ModKeys.meta, key};
  let ctrl_shift = key => {mod_keys: ModKeys.ctrl_shift, key};
  let ctrl_alt = key => {mod_keys: ModKeys.ctrl_alt, key};
  let meta_shift = key => {mod_keys: ModKeys.meta_shift, key};

  let matches = (kc, evt: Js.t(Dom_html.keyboardEvent)) =>
    ModKeys.matches(kc.mod_keys, evt) && Key.matches(kc.key, evt);

  let name = kc => {
    let mod_prefix = ModKeys.mod_prefix(kc.mod_keys);
    mod_prefix ++ kc.key.plain_name;
  };

  let enter = plain(Key.code2("Enter", "Enter", "NumpadEnter"));
  let escape = plain(Key.the_code("Escape"));
  let backspace = plain(Key.the_code("Backspace"));
  let delete = plain(Key.the_code("Delete"));
  let tab = plain(Key.the_code("Tab"));
  let shift_tab = shift(Key.the_code("Tab"));
  let space = plain(Key.the_code("Space"));
  let lt = no_ctrl_alt_meta(Key.the_key("<"));
  let gt = no_ctrl_alt_meta(Key.the_key(">"));
  let colon = no_ctrl_alt_meta(Key.the_key(":"));
  let backslash = no_ctrl_alt_meta(Key.the_key("\\"));
  let left_parens = no_ctrl_alt_meta(Key.the_key("("));
  let right_parens = no_ctrl_alt_meta(Key.the_key(")"));
  let left_bracket = no_ctrl_alt_meta(Key.the_key("["));
  let right_bracket = no_ctrl_alt_meta(Key.the_key("]"));
  let qmark = no_ctrl_alt_meta(Key.the_key("?"));
  let equals = no_ctrl_alt_meta(Key.the_key("="));
  let pound = no_ctrl_alt_meta(Key.the_key("#"));
  let plus = no_ctrl_alt_meta(Key.the_key("+"));
  let minus = no_ctrl_alt_meta(Key.the_key("-"));
  let asterisk = no_ctrl_alt_meta(Key.the_key("*"));
  let slash = no_ctrl_alt_meta(Key.the_key("/"));
  let semicolon = no_ctrl_alt_meta(Key.the_key(";"));
  let comma = no_ctrl_alt_meta(Key.the_key(","));
  let vbar = no_ctrl_alt_meta(Key.the_key("|"));
  let ampersand = no_ctrl_alt_meta(Key.the_key("&"));
  let dollar = no_ctrl_alt_meta(Key.the_key("$"));
  let amp = no_ctrl_alt_meta(Key.the_key("&"));
  let alt_L = alt(Key.the_key("l"));
  let alt_R = alt(Key.the_key("r"));
  let alt_C = alt(Key.the_key("c"));
  let alt_PageUp = alt(Key.the_key("PageUp"));
  let alt_PageDown = alt(Key.the_key("PageDown"));
  let alt_T = alt(Key.the_key("T"));
  let alt_F = alt(Key.the_key("F"));
  let ctrl_z = ctrl(Key.the_key("z"));
  let ctrl_shift_z = ctrl_shift(Key.the_key("Z"));
  let ctrl_alt_i = ctrl_alt(Key.the_key("i"));
  let ctrl_alt_k = ctrl_alt(Key.the_key("k"));
  let ctrl_alt_j = ctrl_alt(Key.the_key("j"));
  let ctrl_alt_l = ctrl_alt(Key.the_key("l"));
  let meta_z = ctrl(Key.the_key("z"));
  let meta_shift_z = ctrl_shift(Key.the_key("Z"));
};
