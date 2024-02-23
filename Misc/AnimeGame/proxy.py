from mitmproxy import http
from mitmproxy import ctx

USE_SSL = False
REMOTE_HOST = "127.0.0.1"
REMOTE_PORT = 28081

class AnimeGame_Proxy:

    LIST_DOMAINS = [
        "dispatchcntest.yuanshen.com",
        "api-beta-sdk.mihoyo.com",
        "api-beta-sdk-os.mihoyo.com",
        "cnbeta01dispatch.yuanshen.com",
        "cnbeta02dispatch.yuanshen.com",
        "gameapi-account.mihoyo.com",
        "minor-api.mihoyo.com",


        "dispatchosglobal.yuanshen.com",
        "dispatchcnglobal.yuanshen.com",
        "osusadispatch.yuanshen.com",
        "oseurodispatch.yuanshen.com",
        "osasiadispatch.yuanshen.com",

        "hk4e-api-os-static.mihoyo.com",
        "hk4e-api-static.mihoyo.com",
        "hk4e-api-os.mihoyo.com",
        "hk4e-api.mihoyo.com",
        "hk4e-sdk-os.mihoyo.com",
        "hk4e-sdk.mihoyo.com",

        "account.mihoyo.com",
        "api-os-takumi.mihoyo.com",
        "api-takumi.mihoyo.com",
        "sdk-os-static.mihoyo.com",
        "sdk-static.mihoyo.com",
        "webstatic-sea.mihoyo.com",
        "webstatic.mihoyo.com",
        "uploadstatic-sea.mihoyo.com",
        "uploadstatic.mihoyo.com",

        "api-os-takumi.hoyoverse.com",
        "sdk-os-static.hoyoverse.com",
        "sdk-os.hoyoverse.com",
        "webstatic-sea.hoyoverse.com",
        "uploadstatic-sea.hoyoverse.com",
        "api-takumi.hoyoverse.com",
        "sdk-static.hoyoverse.com",
        "sdk.hoyoverse.com",
        "webstatic.hoyoverse.com",
        "uploadstatic.hoyoverse.com",
        "account.hoyoverse.com",
        "api-account-os.hoyoverse.com",
        "api-account.hoyoverse.com",

        "hk4e-api-os.hoyoverse.com",
        "hk4e-api-os-static.hoyoverse.com",
        "hk4e-sdk-os.hoyoverse.com",
        "hk4e-sdk-os-static.hoyoverse.com",
        "hk4e-api.hoyoverse.com",
        "hk4e-api-static.hoyoverse.com",
        "hk4e-sdk.hoyoverse.com",
        "hk4e-sdk-static.hoyoverse.com",


        "autopatchhk.yuanshen.com"
    ]
    LIST_BAD_DOMAINS = [
        "log-upload.mihoyo.com",
        "log-upload-os.mihoyo.com",
        "log-upload-os.hoyoverse.com",
        "devlog-upload.mihoyo.com",
        "overseauspider.yuanshen.com"
    ]

    def request(self, flow: http.HTTPFlow) -> None:
        if flow.request.host in self.LIST_BAD_DOMAINS:
            flow.kill() #flow.request.host = "0.0.0.0"
            return

        #allow updates????
        if flow.request.host == "autopatchhk.yuanshen.com":
            if flow.request.pretty_url.endswith("/General/AssetBundles/data_versions"):
                flow.response = http.Response.make(
                    200,
                    open('./www/data_versions', 'rb').read(),
                    {"Content-Type": "application/octet-stream"}
                )
                ctx.log.warn('<====== redirect autopatchhk data_versions ======>')
                return
            if flow.request.pretty_url.endswith("General/AssetBundles/blocks/00/29342328.blk"):
                flow.response = http.Response.make(
                    200,
                    open('./www/29342328.blk', 'rb').read(),
                    {"Content-Type": "application/octet-stream"}
                )
                ctx.log.warn('<======  redirect autopatchhk 29342328.blk ======>')
                return

        if flow.request.host in self.LIST_DOMAINS:
            if USE_SSL:
                flow.request.scheme = "https"
            else:
                flow.request.scheme = "http"
            flow.request.host = REMOTE_HOST
            flow.request.port = REMOTE_PORT
            
    def response(self, flow):
        flow.response.headers["X-MITM-REDIRECT"] = "True"

addons = [
	AnimeGame_Proxy()
]
