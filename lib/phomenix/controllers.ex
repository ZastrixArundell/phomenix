defmodule Phomenix.Controllers do

  alias __MODULE__.Controller

  def get_controllers do
    GenServer.call(:controller, :info)
    |> Map.get(:channels)
    |> Enum.map(&extract/1)
  end

  def get_controller!(id) do
    GenServer.call(:controller, :info)
    |> Map.get(:channels)
    |> Enum.filter(fn {_pid, {_module, _leave, [controller_id, _payload]}} -> controller_id == id end)
    |> List.first()
    |> extract()
  end

  def extract(nil), do: nil

  def extract({_pid, {_module, _leave, [id, payload]}}) do
    %Controller{
      id: id,
      name: payload["name"],
      ac_mode: Enum.member?(payload["types"], "acMode"),
      rgb_mode: Enum.member?(payload["types"], "rgbMode")}
  end

end
