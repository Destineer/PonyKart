﻿using Miyagi.UI;
using Miyagi.UI.Controls;
using Ponykart.Core;
using Ponykart.Levels;
using Ponykart.UI;

namespace Ponykart.Handlers {
	[Handler(HandlerScope.Global)]
	public class CountdownUIHandler {
		private Label countLabel;
		private GUI countGui;

		public CountdownUIHandler() {
			// set up our label
			countGui = LKernel.GetG<UIMain>().GetGUI("countdown gui");

			countLabel = countGui.GetControl<Label>("countdown label");

			// hook up to events
			LKernel.GetG<RaceCountdown>().OnCountdown += new RaceCountdownEvent(OnCountdown);
			LKernel.GetG<LevelManager>().OnLevelPreUnload += new LevelEvent(OnLevelPreUnload);
		}

		void OnLevelPreUnload(LevelChangedEventArgs eventArgs) {
			countGui.Visible = false;
		}


		void OnCountdown(RaceCountdownState state) {
			switch (state) {
				case RaceCountdownState.Three:
					countGui.Visible = true;
					countLabel.Text = "3";
					break;
				case RaceCountdownState.Two:
					countLabel.Text = "2";
					break;
				case RaceCountdownState.One:
					countLabel.Text = "1";
					break;
				case RaceCountdownState.Go:
					countLabel.Text = "Go!";
					break;
				case RaceCountdownState.OneSecondAfterGo:
					countGui.Visible = false;
					break;
			}
		}
	}
}
