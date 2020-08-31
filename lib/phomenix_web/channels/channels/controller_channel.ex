defmodule PhomenixWeb.ControllerChannel do
  use Phoenix.Channel
  alias Phomenix.Controllers.Watcher

  def join("controller:" <> controller_name, payload, socket) do
    socket = socket |> assign(:name, payload["name"])
    :ok = Watcher.monitor(:controller, self(), {__MODULE__, :leave, [controller_name, payload]})
    {:ok, socket}
  end

  def send_ir_to_controller(controller_id, code) do
    PhomenixWeb.Endpoint.broadcast!("controller:#{controller_id}", "ir_write", %{code: code})
  end

  require Logger

  def leave(room_id, user_id) do
    Logger.info("Left #{room_id} #{user_id}")
  end
end
