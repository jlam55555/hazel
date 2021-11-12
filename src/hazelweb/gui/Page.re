open Virtual_dom.Vdom;
open Node;
open ViewUtil;

let logo_panel =
  a(
    [Attr.classes(["logo-text"]), Attr.href("https://hazel.org")],
    [text("Hazel")],
  );

let top_bar = (~inject, ~model: Model.t) => {
  div(
    [Attr.classes(["top-bar"])],
    [
      logo_panel,
      CardsPanel.view(~inject, ~model),
      ActionMenu.view(~inject),
    ],
  );
};

let left_sidebar = (~inject, ~model: Model.t) =>
  Sidebar.left(~inject, ~is_open=model.left_sidebar_open, () =>
    [ActionPanel.view(~inject, model)]
  );

let right_sidebar =
    (~inject, ~model: Model.t, ~result as {assert_map, hii, _}: Result.t) => {
  Sidebar.right(~inject, ~is_open=model.right_sidebar_open, () =>
    [
      AssertPanel.view(~inject, ~model, ~assert_map),
      ContextInspector.view(~inject, ~model, ~hii),
      UndoHistoryPanel.view(~inject, model),
      SettingsPanel.view(~inject, model.settings),
    ]
  );
};

let type_label = div([Attr.class_("label")], [text("Result of type: ")]);

let type_view = (ty: HTyp.t): Node.t => {
  div([Attr.class_("cell-type")], [type_label, HTypCode.view(ty)]);
};

let result_view = (~inject, ~model: Model.t, ~result: DHExp.t): Node.t =>
  div_if(
    model.settings.evaluation.evaluate,
    [Attr.classes(["cell-result"])],
    [
      DHCode.view(
        ~inject,
        ~selected_instance=Model.get_selected_hole_instance(model),
        ~font_metrics=model.font_metrics,
        ~settings=model.settings.evaluation,
        ~width=80,
        result,
      ),
    ],
  );

let branch_panel = {
  let git =
    Printf.sprintf(
      "[%s @ %s (%s)]",
      Version_autogenerated.branch,
      Version_autogenerated.commit_hash_short,
      Version_autogenerated.commit_time,
    );
  span([Attr.id("branch-panel")], [text(git)]);
};

let card_caption = model =>
  div(
    [Attr.class_("card-caption")],
    [Model.get_card(model).info.caption],
  );

let font_specimen =
  /* font-specimen used to gather font metrics for caret positioning and other things */
  div([Attr.id(ViewUtil.font_specimen_id)], [text("X")]);

let code_view = (~inject, ~model: Model.t): Node.t =>
  UHCode.view(
    ~inject,
    ~font_metrics=model.font_metrics,
    ~settings=model.settings,
    ~cursor_inspector=model.cursor_inspector,
    ~program=Model.get_program(model),
  );

let cell_view = (~inject, ~model: Model.t) => {
  TimeUtil.measure_time(
    "Cell.view",
    model.settings.performance.measure && model.settings.performance.cell_view,
    () =>
    div(
      [Attr.id(ViewUtil.cell_id)],
      [font_specimen, code_view(~inject, ~model)],
    )
  );
};

let card_panel =
    (~inject, ~model, ~result as {result, result_ty, _}: Result.t): Node.t =>
  div(
    [Attr.id(ViewUtil.card_dom_id)],
    [
      card_caption(model),
      cell_view(~inject, ~model),
      result_view(~model, ~inject, ~result),
      type_view(result_ty),
    ],
  );

let view = (~inject, ~model: Model.t, ~result: Result.t): Node.t => {
  div(
    [Attr.id("root")],
    [
      top_bar(~inject, ~model),
      left_sidebar(~inject, ~model),
      card_panel(~inject, ~model, ~result),
      right_sidebar(~inject, ~model, ~result),
      branch_panel,
    ],
  );
};
