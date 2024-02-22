module.exports = {
   name: 'ping',
   aliases: [],
   description: 'Command description',
   reqArgs: false,
   usage: '',
   exampleUsage: 'ping',
   category: 'Misc',
   cooldown: 3000,

   async run(ctx) {
      ctx.sendText("PONG");
   }
};
