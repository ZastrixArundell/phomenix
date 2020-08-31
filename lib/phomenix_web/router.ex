defmodule PhomenixWeb.Router do
  use PhomenixWeb, :router
  import Plug.BasicAuth

  pipeline :browser do
    plug :accepts, ["html"]
    plug :fetch_session
    plug :fetch_flash
    plug :protect_from_forgery
    plug :put_secure_browser_headers
    plug :basic_auth, Application.get_env(:phomenix, __MODULE__)
  end

  pipeline :api do
    plug :accepts, ["json"]
  end

  scope "/", PhomenixWeb do
    pipe_through :browser

    get "/", ControllerController, :index
    get "/:id", ControllerController, :show
  end

  # Other scopes may use custom stacks.
  # scope "/api", PhomenixWeb do
  #   pipe_through :api
  # end
end
