open Virtual_dom.Vdom;
open Node;
let logo_panel =
  a(
    [Attr.classes(["logo-text"]), Attr.href("https://hazel.org")],
    [text("Hazel")],
  );

let top_bar = (~inject: ModelAction.t => Ui_event.t, ~model: Model.t) => {
  div(
    [Attr.classes(["top-bar"])],
    [
      logo_panel,
      CardsPanel.view(~inject, ~model),
      ActionMenu.view(~inject),
    ],
  );
};

let cell_status_panel = (~settings: Settings.t, ~model: Model.t, ~inject) => {
  let program = Model.get_program(model);
  let selected_instance = Model.get_selected_hole_instance(model);
  let (_, ty, _) = program.edit_state;
  let result =
    settings.evaluation.show_unevaluated_expansion
      ? program |> Program.get_expansion
      : program |> Program.get_result |> Result.get_dhexp;
  div(
    [],
    [
      div(
        [Attr.classes(["cell-status"])],
        [
          div(
            [Attr.classes(["type-indicator"])],
            [
              div(
                [Attr.classes(["type-label"])],
                [text("Result of type: ")],
              ),
              div([Attr.classes(["htype-view"])], [HTypCode.view(ty)]),
            ],
          ),
        ],
      ),
      div(
        [Attr.classes(["result-view"])],
        [
          DHCode.view(
            ~inject,
            ~selected_instance,
            ~settings=settings.evaluation,
            ~width=80,
            ~font_metrics=model.font_metrics,
            result,
          ),
        ],
      ),
    ],
  );
};

let left_sidebar = (~inject: ModelAction.t => Event.t, ~model: Model.t) =>
  Sidebar.left(~inject, ~is_open=model.left_sidebar_open, () =>
    [ActionPanel.view(~inject, model)]
  );

let right_sidebar = (~inject: ModelAction.t => Event.t, ~model: Model.t) => {
  let settings = model.settings;
  let program = Model.get_program(model);
  let selected_instance = Model.get_selected_hole_instance(model);
  Sidebar.right(
    ~inject,
    ~is_open=model.settings.right_panel.panel_open,
    [
      (
        model.settings.right_panel.code_summary,
        Node.text("SU"),
        inject(ModelAction.UpdateSettings(RightPanel(Toggle_code_summary))),
        () => CodeSummary.view(),
      ),
      (
        model.settings.right_panel.code_explanation,
        Node.text("EX"),
        inject(
          ModelAction.UpdateSettings(RightPanel(Toggle_code_explanation)),
        ),
        () => CodeExplanation.view(),
      ),
      (
        model.settings.right_panel.cursor_inspector,
        Node.text("CI"),
        inject(
          ModelAction.UpdateSettings(RightPanel(Toggle_cursor_inspector)),
        ),
        () => CursorInspector.view(~inject, model),
      ),
      (
        model.settings.right_panel.context_inspector,
        Node.text("CX"),
        inject(
          ModelAction.UpdateSettings(RightPanel(Toggle_context_inspector)),
        ),
        () =>
          ContextInspector.view(
            ~inject,
            ~selected_instance,
            ~settings=settings.evaluation,
            ~font_metrics=model.font_metrics,
            program,
          ),
      ),
      (
        model.settings.right_panel.undo_history_panel,
        Node.text("H"),
        inject(
          ModelAction.UpdateSettings(RightPanel(Toggle_undo_history_panel)),
        ),
        () => UndoHistoryPanel.view(~inject, model),
      ),
      (
        model.settings.right_panel.settings_panel,
        Node.text("SE"),
        inject(
          ModelAction.UpdateSettings(RightPanel(Toggle_settings_panel)),
        ),
        () => SettingsPanel.view(~inject, settings),
      ),
    ],
  );
};

let view = (~inject: ModelAction.t => Event.t, model: Model.t) => {
  let settings = model.settings;
  TimeUtil.measure_time(
    "Page.view",
    settings.performance.measure && settings.performance.page_view,
    () => {
      let card_caption = Model.get_card(model).info.caption;
      let cell_status =
        !settings.evaluation.evaluate
          ? div([], []) : cell_status_panel(~settings, ~model, ~inject);
      div(
        [Attr.id("root")],
        [
          top_bar(~inject, ~model),
          div(
            [Attr.classes(["main-area"])],
            [
              left_sidebar(~inject, ~model),
              div(
                [Attr.classes(["flex-wrapper"])],
                [
                  div(
                    [Attr.id("page-area")],
                    [
                      div(
                        [Attr.classes(["page"])],
                        [
                          div(
                            [Attr.classes(["card-caption"])],
                            [card_caption],
                          ),
                          Cell.view(~inject, model),
                          cell_status,
                        ],
                      ),
                      div(
                        [
                          Attr.style(
                            Css_gen.(
                              white_space(`Pre) @> font_family(["monospace"])
                            ),
                          ),
                        ],
                        [],
                      ),
                    ],
                  ),
                ],
              ),
              right_sidebar(~inject, ~model),
            ],
          ),
        ],
      );
    },
  );
};
