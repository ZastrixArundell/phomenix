defmodule PhomenixWeb.ControllerSocket do
  use Phoenix.Socket

  @secret_auth_key Application.get_env(:phomenix, __MODULE__, %{})[:secret_auth_key]

  channel "controller:*", PhomenixWeb.ControllerChannel

  def connect(params, socket, _connect_info) do
    require Logger

    if params["secret_key"] == @secret_auth_key do
      {:ok, socket}
    else
      Logger.error "Someone tried to connect with this secret key: '#{params["secret_key"]}' but failed"
      :error
    end
  end

  def id(_socket), do: nil
end
