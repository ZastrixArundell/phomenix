defmodule PhomenixWeb.ControllerController do
  use PhomenixWeb, :controller

  alias Phomenix.Controllers
  alias PhomenixWeb.ControllerChannel

  def index(conn, _params) do
    controller = Controllers.get_controllers()
    render(conn, "index.html", controller: controller)
  end

  def show(conn, %{"id" => id}) do
    controller = Controllers.get_controller!(id)

    if !!controller do
      render(conn, "show.html", controller: controller)
    else
      conn
      |> put_flash(:error, "Controller #{id} not found!")
      |> redirect(to: Routes.controller_path(conn, :index))
    end
  end

  def update(conn, %{"id" => id, "code" => code}) do
    ControllerChannel.send_ir_to_controller(id, code)
    redirect(conn, to: Routes.controller_path(conn, :index))
  end
end
