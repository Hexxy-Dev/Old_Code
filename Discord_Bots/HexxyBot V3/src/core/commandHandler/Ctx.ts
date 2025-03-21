import Color from '../graphics/colors';

export class Ctx {
   message: any;
   channel: any;
   guild: any;
   user: any;
   member: any;
   commandName: string;
   args: string[];

   constructor(message, commandName, args) {
      this.message = message;
      this.channel = message.channel;
      this.guild = message.guild;

      this.user = message.author;
      this.member = message.member;

      this.commandName = commandName;
      this.args = args;
   }

   hasRole(roleName) : boolean {
      let result = false;
      this.member.roles.cache.forEach((role) => {
         if(role.name == roleName)
            result = true;
      });
      return result;
   }

   async react(reaction) {
      await this.message.react(reaction);
   }

   async sendText(text, options = {}) {
      await this.channel.send(text, options);
   }

   async sendEmbed(embed, options = {}) {
      await this.channel.send(embed, options);
   }

   async sendTextAndEmbed(text, embed, options : any) {
      options.embed = embed;
      await this.channel.send(text, options);
   }

   // Gets the bot color in the server where the message has been sent
   // or the primary color set in the colors.js file
   get hexColor() {
      return this.guild ? this.guild.me.displayHexColor : Color.Primary;
   }

   // Other useful getters
   get guildID() {
      return this.guild ? this.guild.id : null;
   }

   get userID() {
      return this.user.id;
   }

   get channelID() {
      return this.channel.id;
   }
};
